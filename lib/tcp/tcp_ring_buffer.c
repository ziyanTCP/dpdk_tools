//
// Created by Ziyan Wu on 11/16/19.
//
#include "tcp_ring_buffer.h"
struct fragment_ctx * AllocateFragmentContext(struct rb_manager * rbm)
{
  /* this function should be called only in mtcp thread */
  struct fragment_ctx *frag;

  /* first try deqeue the fragment in free fragment queue */
  frag = RBFragDequeue(rbm->free_fragq);
  if (!frag) {
    frag = RBFragDequeue(rbm->free_fragq_int);
    if (!frag) {
      /* next fall back to fetching from mempool */
      //frag = MPAllocateChunk(rbm->frag_mp);
      int rc = rte_mempool_get(rbm->frag_mp, (void **)&frag);
      if (!frag) {
        //TRACE_ERROR("fragments depleted, fall back to calloc\n");
        frag = calloc(1, sizeof(struct fragment_ctx));
        if (frag == NULL) {
          //TRACE_ERROR("calloc failed\n");
          exit(-1);
        }
        frag->is_calloc = 1; /* mark it as allocated by calloc */
      }
    }
  }
  memset(frag, 0, sizeof(*frag));
  return frag;
}

struct tcp_ring_buffer* RBInit(struct tcp_instance * my_tcp, uint32_t init_seq)
{
  struct tcp_ring_buffer* buff = (struct tcp_ring_buffer*)calloc(1, sizeof(struct tcp_ring_buffer));

  if (buff == NULL){
    perror("rb_init buff");
    return NULL;
  }

  int rc =  rte_mempool_get(my_tcp->rbm_rcv->mp , (void **)&buff->data);

  //memset(buff->data, 0, rbm->chunk_size);

  buff->size = my_tcp->rbm_rcv->chunk_size;
  buff->head = buff->data;
  buff->head_seq = init_seq; // head_seq form RBInit from ProcessTCPPayload is  rcvvar->irs + 1 , which is seq in HandlePassiveOpen
  buff->init_seq = init_seq;
  buff->head_offset = buff->head - buff->data;

  my_tcp->rbm_rcv->cur_num++;

  return buff;
}

static inline uint32_t
GetMinSeq(uint32_t a, uint32_t b)
{
  if (a == b) return a;
  if (a < b)
    return ((b - a) <= MAXSEQ/2) ? a : b;
  /* b < a */
  return ((a - b) <= MAXSEQ/2) ? b : a;
}


static inline uint32_t
GetMaxSeq(uint32_t a, uint32_t b)
{
  if (a == b) return a;
  if (a < b)
    return ((b - a) <= MAXSEQ/2) ? b : a;
  /* b < a */
  return ((a - b) <= MAXSEQ/2) ? a : b;
}


static inline int
CanMerge(const struct fragment_ctx *a, const struct fragment_ctx *b)
{
  uint32_t a_end = a->seq + a->len + 1;
  uint32_t b_end = b->seq + b->len + 1;

  if (GetMinSeq(a_end, b->seq) == a_end ||
      GetMinSeq(b_end, a->seq) == b_end)
    return 0;
  return (1);
}

static inline void
MergeFragments(struct fragment_ctx *a, struct fragment_ctx *b)
{
	/* merge a into b */
	uint32_t min_seq, max_seq;

	min_seq = GetMinSeq(a->seq, b->seq);
	max_seq = GetMaxSeq(a->seq + a->len, b->seq + b->len);
	b->seq  = min_seq;
	b->len  = max_seq - min_seq;
}

static inline void
FreeFragmentContextSingle(struct rb_manager * rbm, struct fragment_ctx* frag)
{
  if (frag->is_calloc)
    free(frag);
  else
    rte_mempool_put(rbm->frag_mp, frag);
}


int RBPut(struct rb_manager * rbm, struct tcp_ring_buffer* buff, void* data, uint32_t len, uint32_t cur_seq){
  int putx, end_off;
  struct fragment_ctx *new_ctx;
  struct fragment_ctx* iter;
  struct fragment_ctx* prev, *pprev;
  int merged = 0;

  if (len <= 0)
    return 0;

  if (GetMinSeq(buff->head_seq, cur_seq) != buff->head_seq)
    return 0;

  putx = cur_seq - buff->head_seq;
  end_off = putx + len;

  if (buff->size < end_off) {
    return -2;
  }

  if (buff->size <= (buff->head_offset + end_off)) {
    memmove(buff->data, buff->head, buff->last_len);
    buff->tail_offset -= buff->head_offset;
    buff->head_offset = 0;
    buff->head = buff->data;
  }
  memcpy(buff->head + putx, data, len);

  if (buff->tail_offset < buff->head_offset + end_off)
    buff->tail_offset = buff->head_offset + end_off;
  buff->last_len = buff->tail_offset - buff->head_offset;

  // create fragmentation context blocks
  //TODO:
  new_ctx = AllocateFragmentContext(rbm);
  /*
  if (!new_ctx) {
    perror("allocating new_ctx failed");
    return 0;
  }
   */

  new_ctx->seq  = cur_seq;
  new_ctx->len  = len;
  new_ctx->next = NULL;

  // traverse the fragment list, and merge the new fragment if possible
  for (iter = buff->fctx, prev = NULL, pprev = NULL;
       iter != NULL;
       pprev = prev, prev = iter, iter = iter->next) {

    if (CanMerge(new_ctx, iter)) {
      /* merge the first fragment into the second fragment */
      MergeFragments(new_ctx, iter);

      /* remove the first fragment */
      if (prev == new_ctx) {
        if (pprev)
          pprev->next = iter;
        else
          buff->fctx = iter;
        prev = pprev;
      }
      FreeFragmentContextSingle(rbm, new_ctx);
      new_ctx = iter;
      merged = 1;
    }
    else if (merged ||
        GetMaxSeq(cur_seq + len, iter->seq) == iter->seq) {
      /* merged at some point, but no more mergeable
         then stop it now */
      break;
    }
  }

  if (!merged) {
    if (buff->fctx == NULL) {
      buff->fctx = new_ctx;
    } else if (GetMinSeq(cur_seq, buff->fctx->seq) == cur_seq) {
      /* if the new packet's seqnum is before the existing fragments */
      new_ctx->next = buff->fctx;
      buff->fctx = new_ctx;
    } else {
      /* if the seqnum is in-between the fragments or
         at the last */
      //assert(GetMinSeq(cur_seq, prev->seq + prev->len) == prev->seq + prev->len);
      prev->next = new_ctx;
      new_ctx->next = iter;
    }
  }
  if (buff->head_seq == buff->fctx->seq) {
    buff->cum_len += buff->fctx->len - buff->merged_len;
    buff->merged_len = buff->fctx->len;
  }

  return len;
}
