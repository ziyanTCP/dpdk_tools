//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_CONN_ACTOR_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_CONN_ACTOR_H_
//#include "shared.h"
//#include "calf/calf_pkt.h"
//#include "calf/tts.h"  // OFFSET_PKT_TYPE
#include "middleman/actor.h"
#include "middleman/actor_struct.h"
//#include <arpa/inet.h>

#include <rte_malloc.h> //rte_malloc
#include "middleman/actors/tcp_conn/base.h"
#include "middleman/actors/tcp_conn/hashtable.h"
#include "middleman/actors/tcp_conn/tcp_ring_buffer.h"




struct actor_tcp_conn {
  struct rte_mempool* flow_pool;		/* memory pool for tcp_stream */
  struct rte_mempool* rv_pool;			/* memory pool for recv variables */
  struct rte_mempool* sv_pool;			/* memory pool for send variables */
  struct rte_mempool* mv_pool;			/* memory pool for monitor variables */


  //struct mbuf_table rmbufs[10]; //10 is the number of ports
  //struct mbuf_table wmbufs[10];


  // put state for mtcp here
  struct rte_ring *mmtx;
  struct actor *cur;
  //tcp_stream tcp_s[100];
  struct hashtable *tcp_flow_table;
  struct hashtable *listeners;

  uint32_t g_id;			/* id space in a thread */
  uint32_t flow_cnt;		/* number of concurrent flows */

  struct rb_manager* rbm_rcv;
};


#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_CONN_ACTOR_H_
