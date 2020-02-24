//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_SOCKET_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_SOCKET_H_
#include "base.h"
#include "tcp_stream_queue.h"

struct socket_map
{
  int id;
  int socktype;
  uint32_t opts;
  struct sockaddr_in src_addr;
  union {
    struct tcp_stream *stream;
    struct tcp_listener *listener;
    struct mtcp_epoll *ep;
    struct pipe *pp;
  };
  //uint32_t epoll;			/* registered events */
  //uint32_t events;		/* available events */
  //mtcp_epoll_data_t ep_data;
  TAILQ_ENTRY (socket_map) free_smap_link;
};

typedef struct socket_map * socket_map_t;

struct tcp_listener
{
  int sockid;
  socket_map_t socket;
  int backlog;
  stream_queue_t acceptq;
  //pthread_mutex_t accept_lock;
  //pthread_cond_t accept_cond;
  TAILQ_ENTRY(tcp_listener) he_link;	/* hash table entry link */
};

#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_SOCKET_H_
