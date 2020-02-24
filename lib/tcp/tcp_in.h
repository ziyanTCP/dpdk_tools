//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_IN_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_IN_H_
#include <rte_ip.h>
#include <rte_tcp.h>
#include "tcp.h"
#include "tcp_stream.h"
#include "tcp_out.h"
#include <unistd.h> // notice this! you need it!

#define TCP_DEFAULT_MSS			1460
enum tcp_state
{
  TCP_ST_CLOSED		= 0,
  TCP_ST_LISTEN		= 1,
  TCP_ST_SYN_SENT		= 2,
  TCP_ST_SYN_RCVD		= 3,
  TCP_ST_ESTABLISHED	= 4,
  TCP_ST_FIN_WAIT_1	= 5,
  TCP_ST_FIN_WAIT_2	= 6,
  TCP_ST_CLOSE_WAIT	= 7,
  TCP_ST_CLOSING		= 8,
  TCP_ST_LAST_ACK		= 9,
  TCP_ST_TIME_WAIT	= 10
};

enum tcp_close_reason
{
  TCP_NOT_CLOSED		= 0,
  TCP_ACTIVE_CLOSE	= 1,
  TCP_PASSIVE_CLOSE	= 2,
  TCP_CONN_FAIL		= 3,
  TCP_CONN_LOST		= 4,
  TCP_RESET			= 5,
  TCP_NO_MEM			= 6,
  TCP_NOT_ACCEPTED	= 7,
  TCP_TIMEDOUT		= 8
};


struct tcp_stream * CreateNewFlowHTEntry(struct tcp_instance *my_tcp, struct rte_tcp_hdr* pkt_tcp_hdr,struct rte_ipv4_hdr* pkt_ip_hdr);
struct tcp_stream * HandlePassiveOpen(struct tcp_instance * my_tcp, struct rte_ipv4_hdr *pkt_ip_hdr, struct rte_tcp_hdr* pkt_tcp_hdr);
//TODO: static inline
void Handle_TCP_ST_LISTEN (
        struct tcp_instance * my_tcp,
        struct tcp_stream* cur_stream,
        struct rte_tcp_hdr* pkt_tcp_hdr,
        struct rte_ether_hdr* pkt_eth_hdr);
//TODO: static inline
void Handle_TCP_ST_SYN_RCVD (struct tcp_instance * my_tcp, struct tcp_stream* cur_stream, struct rte_tcp_hdr* pkt_tcp_hdr);
#endif