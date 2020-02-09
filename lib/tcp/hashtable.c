//
// Created by Ziyan Wu on 11/9/19.
//
#include "hashtable.h"

unsigned int HashFlow(const void *f)
{
  tcp_stream *flow = (tcp_stream *)f;
  unsigned long hash = 5381;
	int c;
	int index;
    //printf("src_addr:%u\n",flow->src_addr);
    //printf("src_port:%u\n",flow->src_port);
	char *str = (char *)&flow->src_addr;

	index = 0;

	while ((c = *str++) && index++ < 12) {
		if (index == 8) {
			str = (char *)&flow->src_port;
		}
		hash = ((hash << 5) + hash) + c;
	}

	return hash & (NUM_BINS_FLOWS - 1);
}
int EqualFlow(const void *f1, const void *f2)
{
  tcp_stream *flow1 = (tcp_stream *)f1;
  tcp_stream *flow2 = (tcp_stream *)f2;

  return (flow1->src_addr == flow2->src_addr &&
      flow1->src_port == flow2->src_port &&
      flow1->dst_addr == flow2->dst_addr &&
      flow1->dst_port == flow2->dst_port);
}
int EqualListener(const void *l1, const void *l2)
{
  struct tcp_listener *listener1 = (struct tcp_listener *)l1;
  struct tcp_listener *listener2 = (struct tcp_listener *)l2;
  return (listener1->socket->src_addr.sin_port == listener2->socket->src_addr.sin_port);
}
struct hashtable *CreateHashtable(unsigned int (*hashfn) (const void *), // key function
                                  int (*eqfn) (const void*, const void *),            // equality
                                  int bins) // no of bins
{
  int i;
  struct hashtable* ht = calloc(1, sizeof(struct hashtable));
  if (!ht){
    //RTE_LOG(INFO, ACTOR, "calloc: CreateHashtable");
    return 0;
  }

  ht->hashfn = hashfn;
  ht->eqfn = eqfn;
  ht->bins = bins;

  /* creating bins */
  if (IS_FLOW_TABLE(hashfn)) {
    ht->ht_table = calloc(bins, sizeof(hash_bucket_head));
    if (!ht->ht_table) {
      //RTE_LOG(INFO, ACTOR, "calloc: CreateHashtable bins!\n");
      free(ht);
      return 0;
    }
    /* init the tables */
    for (i = 0; i < bins; i++)
      TAILQ_INIT(&ht->ht_table[i]);
  } else if (IS_LISTEN_TABLE(hashfn)) {
    ht->lt_table = calloc(bins, sizeof(list_bucket_head));
    if (!ht->lt_table) {
      //RTE_LOG(INFO, ACTOR, "calloc: CreateHashtable bins!\n");
      free(ht);
      return 0;
    }
    /* init the tables */
    for (i = 0; i < bins; i++)
      TAILQ_INIT(&ht->lt_table[i]);
  }

  return ht;
}


void * ListenerHTSearch(struct hashtable *ht, const void *it)
{
  int idx;
  struct tcp_listener item;
  uint16_t port = *((uint16_t *)it);
  struct tcp_listener *walk;
  list_bucket_head *head;
  struct socket_map s;

  s.src_addr.sin_port = port;
  item.socket = &s;

  idx = ht->hashfn(&item);

  head = &ht->lt_table[idx];
  TAILQ_FOREACH(walk, head, he_link) {
    if (ht->eqfn(walk, &item))
      return walk;
  }

  return NULL;
}


unsigned int HashListener(const void *l)
{
  struct tcp_listener *listener = (struct tcp_listener *)l;
  return listener->socket->src_addr.sin_port & (NUM_BINS_LISTENERS - 1);
}

int StreamHTInsert(struct hashtable *ht, void *it) // in CreateTCPStream
{
  /* create an entry*/
  int idx;
  tcp_stream *item = (tcp_stream *)it;

  // assert(ht); TODO: assert

  idx = ht->hashfn(item);
  printf("%u\n",idx);
  //assert(idx >=0 && idx < NUM_BINS_FLOWS); TODO: assert

  TAILQ_INSERT_TAIL(&ht->ht_table[idx], item, rcvvar->he_link);

  item->ht_idx = TCP_AR_CNT;

  return 0;
}

void * StreamHTSearch(struct hashtable *ht, void *it)
{
    int idx;
    tcp_stream *item = ( tcp_stream *)it;
    tcp_stream *walk;
    hash_bucket_head *head;

    idx = ht->hashfn(item);
    //printf("%u\n",idx);
    head = &ht->ht_table[ht->hashfn(item)];
    TAILQ_FOREACH(walk, head, rcvvar->he_link) {
        if (ht->eqfn(walk, item))
            return walk;
    }

    UNUSED(idx);
    return NULL;
}

void* StreamHTRemove(struct hashtable *ht, void *it)
{
  hash_bucket_head *head;
  tcp_stream *item = (tcp_stream *)it;
  int idx = ht->hashfn(item);

  head = &ht->ht_table[idx];
  TAILQ_REMOVE(head, item, rcvvar->he_link);
  return (item);
}