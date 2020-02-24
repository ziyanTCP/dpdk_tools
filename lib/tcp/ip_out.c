//
// Created by Ziyan Wu on 11/9/19.
//
#include "middleman/actors/tcp_conn/ip_out.h"
#include "middleman/actors/tcp_conn/tcp_conn_actor.h"
/*TODO: very strange errors
uint8_t * IPOutputStandalone(struct actor_tcp_conn *mystate, uint8_t protocol,
                   uint16_t ip_id, uint32_t saddr, uint32_t daddr, uint16_t payloadlen)
{
  struct iphdr *iph;
  int nif;
  unsigned char * haddr, is_external;
  int rc = -1;
  iph = (struct NFL_IPV4_HDR *)EthernetOutput(mystate,
                                       ETH_P_IP, nif, haddr, payloadlen + IP_HEADER_LEN);
  if (!iph) {
    return NULL;
  }

  iph->ihl = IP_HEADER_LEN >> 2;
  iph->version = 4;
  iph->tos = 0;
  iph->tot_len = htons(IP_HEADER_LEN + payloadlen);
  iph->id = htons(ip_id);
  iph->frag_off = htons(IP_DF);	// no fragmentation
  iph->ttl = 64;
  iph->protocol = protocol;
  iph->saddr = saddr;
  iph->daddr = daddr;
  iph->check = 0;

  if (rc == -1)
    iph->check = ip_fast_csum(iph, iph->ihl);


  //TODO: OUTPUT
  UNUSED(rc);
  iph->check = ip_fast_csum(iph, iph->ihl);

  return (uint8_t *)(iph + 1);
}
 */

uint8_t * IPOutput(struct actor_tcp_conn *mystate, tcp_stream *stream, uint16_t tcplen){
  struct iphdr *iph;
  int nif;
  unsigned char *haddr, is_external = 0;
  int rc = -1;

  /*
  if (stream->sndvar->nif_out >= 0) {
    nif = stream->sndvar->nif_out;
  } else {
    nif = GetOutputInterface(stream->daddr, &is_external);
    stream->sndvar->nif_out = nif;
    stream->is_external = is_external;
  }

  haddr = GetDestinationHWaddr(stream->daddr, stream->is_external);
  if (!haddr) {
#if 0
    uint8_t *da = (uint8_t *)&stream->daddr;
		TRACE_INFO("[WARNING] The destination IP %u.%u.%u.%u "
				"is not in ARP table!\n",
				da[0], da[1], da[2], da[3]);
#endif
    /* if not found in the arp table, send arp request and return NULL */
    /* tcp will retry sending the packet later */
    //RequestARP(mtcp, (stream->is_external) ? (CONFIG.gateway)->daddr : stream->daddr,
    //           stream->sndvar->nif_out, mtcp->cur_ts);
    //return NULL;
  //}

  iph = (struct iphdr *)EthernetOutput(mystate, ETH_P_IP,
                                       stream->sndvar->nif_out, haddr, tcplen + IP_HEADER_LEN);
  if (!iph) {
    return NULL;
  }
   //TODO: ip field
  iph->ihl = IP_HEADER_LEN >> 2;
  iph->version = 4;
  iph->tos = 0;
  iph->tot_len = htons(IP_HEADER_LEN + tcplen);
  iph->id = htons(stream->sndvar->ip_id++);
  iph->frag_off = htons(0x4000);	// no fragmentation
  iph->ttl = 64;
  iph->protocol = IPPROTO_TCP;
  iph->saddr = stream->saddr;

  return 0;
}