//
// Created by Ziyan Wu on 11/9/19.
//
#include "middleman/actors/tcp_conn/tcp_out.h"
#include "middleman/actors/tcp_conn/tcp_conn_actor.h"
//#include "middleman/actors/tcp_conn/ip_out.h"
int SendTCPPacketStandalone(struct actor_tcp_conn *mystate,
                            uint32_t saddr, uint16_t sport, uint32_t daddr, uint16_t dport,
                            uint32_t seq, uint32_t ack_seq, uint16_t window, uint8_t flags,
                            uint8_t *payload, uint16_t payloadlen,
                            uint32_t cur_ts, uint32_t echo_ts)
{
  //why mystate?
  struct tcphdr *t_hdr;
  uint8_t *tcpopt;
  uint32_t *ts;
  uint16_t optlen;
  int rc = -1;

  optlen = CalculateOptionLength(flags);
  if (payloadlen + optlen > TCP_DEFAULT_MSS) {
    //  TRACE_ERROR("Payload size exceeds MSS.\n");
    //  assert(0);
    return ERROR;
  }

  //t_hdr = (struct tcphdr *)IPOutputStandalone(mystate, IPPROTO_TCP, 0,
    //                                          saddr, daddr, TCP_HEADER_LEN + optlen + payloadlen);
  if (t_hdr == NULL) {
    return ERROR;
  }
  memset(t_hdr, 0, TCP_HEADER_LEN + optlen);

  t_hdr->source = sport;
  t_hdr->dest = dport;

  if (flags & TCP_FLAG_SYN)
    t_hdr->syn = TRUE;
  if (flags & TCP_FLAG_FIN)
    t_hdr->fin = TRUE;
  if (flags & TCP_FLAG_RST)
    t_hdr->rst = TRUE;
  if (flags & TCP_FLAG_PSH)
    t_hdr->psh = TRUE;

  t_hdr->seq = htonl(seq);
  if (flags & TCP_FLAG_ACK) {
    t_hdr->ack = TRUE;
    t_hdr->ack_seq = htonl(ack_seq);
  }

  t_hdr->window = htons(MIN(window, TCP_MAX_WINDOW));

  tcpopt = (uint8_t *)t_hdr + TCP_HEADER_LEN;
  ts = (uint32_t *)(tcpopt + 4);

  tcpopt[0] = TCP_OPT_NOP;
  tcpopt[1] = TCP_OPT_NOP;
  tcpopt[2] = TCP_OPT_TIMESTAMP;
  tcpopt[3] = TCP_OPT_TIMESTAMP_LEN;
  ts[0] = htonl(cur_ts);
  ts[1] = htonl(echo_ts);

  t_hdr->doff = (TCP_HEADER_LEN + optlen) >> 2;
  // copy payload if exist
  if (payloadlen > 0) {
    memcpy((uint8_t *)t_hdr + TCP_HEADER_LEN + optlen, payload, payloadlen);
    /*
#if defined(NETSTAT) && defined(ENABLELRO)
    mystate->nstat.tx_gdptbytes += payloadlen;
#endif
*/
  }

/*
#if TCP_CALCULATE_CHECKSUM
  #ifndef DISABLE_HWCSUM
	uint8_t is_external;
	if (mystate->iom->dev_ioctl != NULL)
		rc = mystate->iom->dev_ioctl(mystate->ctx, GetOutputInterface(daddr, &is_external),
					  PKT_TX_TCPIP_CSUM, NULL);
	UNUSED(is_external);
#endif
	if (rc == -1)
		t_hdr->check = TCPCalcChecksum((uint16_t *)t_hdr,
					      TCP_HEADER_LEN + optlen + payloadlen,
					      saddr, daddr);
#endif
*/
  if (t_hdr->syn || t_hdr->fin) {
    payloadlen++;
  }

  return payloadlen;
}

int SendControlPacket(struct actor_tcp_conn *mystate, tcp_stream *cur_stream, uint32_t cur_ts) {
  struct tcp_send_vars *sndvar = cur_stream->sndvar;
  int ret = 0;

  if (cur_stream->state == TCP_ST_SYN_RCVD) {
    /* Send SYN here */
    ret = SendTCPPacket(mystate, cur_stream, cur_ts, TCP_FLAG_SYN | TCP_FLAG_ACK, NULL, 0);
    //cur_stream->snd_nxt = sndvar->iss;
    return ret;
  }
  else if (cur_stream->state == TCP_ST_CLOSE_WAIT) {
    /* Send ACK for the FIN here */
    ret = SendTCPPacket(mystate, cur_stream, cur_ts, TCP_FLAG_ACK, NULL, 0);
  }
}

int SendTCPPacket(struct actor_tcp_conn *mystate, tcp_stream *cur_stream, uint32_t cur_ts, uint8_t flags, uint8_t *payload, uint16_t payloadlen){

  struct tcphdr *tcph;
  uint16_t optlen;
  uint8_t wscale = 0;
  uint32_t window32 = 0;
  int rc = -1;

  optlen = CalculateOptionLength(flags);
  tcph = (struct tcphdr *)IPOutput(mystate, cur_stream,
                                   TCP_HEADER_LEN + optlen + payloadlen);
  //memset(tcph, 0, TCP_HEADER_LEN + optlen);

  //tcph->source = cur_stream->sport;
  //tcph->dest = cur_stream->dport;

  //rte_eth_tx_burst
  return payloadlen;
}