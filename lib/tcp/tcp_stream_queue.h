//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_STREAM_QUEUE_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_STREAM_QUEUE_H_
typedef uint32_t index_type; //tcp_rb_frag_queue.c

struct stream_queue
{
  index_type _capacity;
  volatile index_type _head;
  volatile index_type _tail;
  struct tcp_stream * volatile * _q;
};
typedef struct stream_queue* stream_queue_t;
#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_STREAM_QUEUE_H_
