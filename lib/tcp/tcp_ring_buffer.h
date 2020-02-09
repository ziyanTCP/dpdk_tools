//
// Created by Ziyan Wu on 11/16/19.
//

#ifndef AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_RING_BUFFER_H_
#define AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_RING_BUFFER_H_
#include "middleman/actors/tcp_conn/tcp_rb_frag_queue.h"

#define MAXSEQ               ((uint32_t)(0xFFFFFFFF))

struct mbuf_table {
  uint16_t len; /* length of queued packets */
  struct rte_mbuf *m_table[MAX_PKT_BURST];
};


struct rb_manager
{
  size_t chunk_size;
  uint32_t cur_num;
  uint32_t cnum;

  struct rte_mempool* mp;
  struct rte_mempool* frag_mp;

  struct rb_frag_queue*  free_fragq;		/* free fragment queue (for app thread) */
  struct rb_frag_queue*  free_fragq_int;	/* free fragment quuee (only for mtcp) */

} rb_manager;


struct fragment_ctx
{
  uint32_t seq;
  uint32_t len : 31;
  uint32_t is_calloc : 1;
  struct fragment_ctx *next;
};


struct tcp_ring_buffer
{
  u_char* data;			/* buffered data */
  u_char* head;			/* pointer to the head */

  uint32_t head_offset;	/* offset for the head (head - data) */
  uint32_t tail_offset;	/* offset fot the last byte (null byte) */

  int merged_len;			/* contiguously merged length */
  uint64_t cum_len;		/* cummulatively merged length */
  int last_len;			/* currently saved data length */
  int size;				/* total ring buffer size */

  /* TCP payload features */
  uint32_t head_seq;
  uint32_t init_seq;

  struct fragment_ctx* fctx;
};


struct tcp_ring_buffer* RBInit(struct actor_tcp_conn * mystate, uint32_t init_seq);

int RBPut(struct rb_manager* rbm, struct tcp_ring_buffer* buff, void* data, uint32_t len, uint32_t cur_seq);

//TODO: static
struct fragment_ctx * AllocateFragmentContext(struct rb_manager * rbm);



#endif //AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_RING_BUFFER_H_
