//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_BASE_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_BASE_H_

//#ifdef HAVE_STDINT_H
# include <stdint.h>
# include <netinet/in.h>
#include <netinet/ip.h>

#include <sys/queue.h>
//#include "shared.h"
//#endif
#define ETH_P_IP	0x0800

#define MAX_CONCURRENCY 1000

#define MAX_PKT_BURST 64

#ifndef TRUE
#define TRUE (1)
#endif

#ifndef FALSE
#define FALSE (0)
#endif

#ifndef ERROR
#define ERROR (-1)
#endif

#ifndef NULL
#define NULL 0
#endif

#define MAX(a, b) ((a)>(b)?(a):(b))
#define MIN(a, b) ((a)<(b)?(a):(b))


#define ETHERNET_HEADER_LEN		14	// sizeof(struct ethhdr)
#define IP_HEADER_LEN			20	// sizeof(struct iphdr)
#define TCP_HEADER_LEN			20	// sizeof(struct tcphdr)
#define TOTAL_TCP_HEADER_LEN		54	// total header length

#ifndef TCP_FLAGS
#define TCP_FLAGS
#define TCP_FLAG_FIN	0x01	// 0000 0001
#define TCP_FLAG_SYN	0x02	// 0000 0010
#define TCP_FLAG_RST	0x04	// 0000 0100
#define TCP_FLAG_PSH	0x08	// 0000 1000
#define TCP_FLAG_ACK	0x10	// 0001 0000
#define TCP_FLAG_URG	0x20	// 0010 0000
#endif

#define TCP_OPT_FLAG_MSS			0x02	// 0000 0010
#define TCP_OPT_FLAG_WSCALE			0x04	// 0000 0100
#define TCP_OPT_FLAG_SACK_PERMIT	0x08	// 0000 1000
#define TCP_OPT_FLAG_SACK			0x10	// 0001 0000
#define TCP_OPT_FLAG_TIMESTAMP		0x20	// 0010 0000

#define TCP_OPT_MSS_LEN			4
#define TCP_OPT_WSCALE_LEN		3
#define TCP_OPT_SACK_PERMIT_LEN	2
#define TCP_OPT_SACK_LEN		10
#define TCP_OPT_TIMESTAMP_LEN	10

#define TCP_MAX_WINDOW 65535
#define TCP_OPT_TIMESTAMP_LEN	10

#define TCP_DEFAULT_MSS			1460
#define TCP_DEFAULT_WSCALE		7
#define TCP_INITIAL_WINDOW		14600	// initial window size


enum tcp_option
{
  TCP_OPT_END			= 0,
  TCP_OPT_NOP			= 1,
  TCP_OPT_MSS			= 2,
  TCP_OPT_WSCALE		= 3,
  TCP_OPT_SACK_PERMIT	= 4,
  TCP_OPT_SACK		= 5,
  TCP_OPT_TIMESTAMP	= 8
};

struct tcphdr {
  u_int16_t   source;
  u_int16_t   dest;
  u_int32_t   seq;
  u_int32_t   ack_seq;
  u_int16_t
      res1:4,
      doff:4,
      fin:1,
      syn:1,
      rst:1,
      psh:1,
      ack:1,
      urg:1,
      ece:1,
      cwr:1;
  u_int16_t   window;
  u_int16_t   check;
  u_int16_t   urg_ptr;
};

#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_BASE_H_
