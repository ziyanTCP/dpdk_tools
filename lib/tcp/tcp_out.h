//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_OUT_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_OUT_H_
#include "middleman/actors/tcp_conn/base.h"
#include "middleman/actors/tcp_conn/tcp_conn_actor.h"
#include "middleman/actors/tcp_conn/tcp_in.h"


int SendTCPPacketStandalone(struct actor_tcp_conn *mystate,
                            uint32_t saddr, uint16_t sport, uint32_t daddr, uint16_t dport,
                            uint32_t seq, uint32_t ack_seq, uint16_t window, uint8_t flags,
                            uint8_t *payload, uint16_t payloadlen,
                            uint32_t cur_ts, uint32_t echo_ts);


int SendTCPPacket(struct actor_tcp_conn *mystate, tcp_stream *cur_stream,
              uint32_t cur_ts, uint8_t flags, uint8_t *payload, uint16_t payloadlen);

//TODO: static inline
int SendControlPacket(struct actor_tcp_conn *mystate, tcp_stream *cur_stream, uint32_t cur_ts);


static inline uint16_t CalculateOptionLength(uint8_t flags)
{
  uint16_t optlen = 0;

  if (flags & TCP_FLAG_SYN) {
    optlen += TCP_OPT_MSS_LEN;
#if TCP_OPT_SACK_ENABLED
    optlen += TCP_OPT_SACK_PERMIT_LEN;
#if !TCP_OPT_TIMESTAMP_ENABLED
		optlen += 2;	// insert NOP padding
#endif /* TCP_OPT_TIMESTAMP_ENABLED */
#endif /* TCP_OPT_SACK_ENABLED */

#if TCP_OPT_TIMESTAMP_ENABLED
    optlen += TCP_OPT_TIMESTAMP_LEN;
#if !TCP_OPT_SACK_ENABLED
		optlen += 2;	// insert NOP padding
#endif /* TCP_OPT_SACK_ENABLED */
#endif /* TCP_OPT_TIMESTAMP_ENABLED */

    optlen += TCP_OPT_WSCALE_LEN + 1;

  } else {

#if TCP_OPT_TIMESTAMP_ENABLED
    optlen += TCP_OPT_TIMESTAMP_LEN + 2;
#endif

#if TCP_OPT_SACK_ENABLED
    if (flags & TCP_FLAG_SACK) {
			optlen += TCP_OPT_SACK_LEN + 2;
		}
#endif
  }

  // TODO: assert(optlen % 4 == 0);

  return optlen;
}

#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_OUT_H_
