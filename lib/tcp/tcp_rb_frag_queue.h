#ifndef TCP_RB_FRAG_QUEUE
#define TCP_RB_FRAG_QUEUE

#include "../dpdk_utility.h"

#ifndef _INDEX_TYPE_
#define _INDEX_TYPE_
typedef uint32_t index_type;
typedef int32_t signed_index_type;
#endif

struct rb_frag_queue
{
  index_type _capacity;
  volatile index_type _head;
  volatile index_type _tail;

  struct fragment_ctx * volatile * _q;
};
/*---------------------------------------------------------------------------*/
// typedef struct rb_frag_queue* rb_frag_queue_t;
/*---------------------------------------------------------------------------*/
struct rb_frag_queue* CreateRBFragQueue(int capacity);
/*---------------------------------------------------------------------------*/
void DestroyRBFragQueue(struct rb_frag_queue*  rb_fragq);
/*---------------------------------------------------------------------------*/
//int RBFragEnqueue(struct rb_frag_queue*  rb_fragq, struct fragment_ctx *frag);
/*---------------------------------------------------------------------------*/
struct fragment_ctx * RBFragDequeue(struct rb_frag_queue*  rb_fragq);
/*---------------------------------------------------------------------------*/

#endif /* TCP_RB_FRAG_QUEUE */