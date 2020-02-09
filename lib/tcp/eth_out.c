//
// Created by Ziyan Wu on 11/15/19.
//

#ifndef AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_ETH_OUT_H_
#define AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_ETH_OUT_H_
#include "middleman/actors/tcp_conn/eth_out.h"
#include <stdint.h>

uint8_t * EthernetOutput(struct actor_tcp_conn *mystate, uint16_t h_proto,
                         int nif, unsigned char* dst_haddr, uint16_t iplen) {
  uint8_t *buf;
  struct ethhdr *ethh;
  int i, eidx;
  //TODO: get write buffer
  //len_of_mbuf = dpc->wmbufs[ifidx].len;
  //m = dpc->wmbufs[ifidx].m_table[len_of_mbuf];


  /* TODO: ethnet header
  ethh = (struct ethhdr *)buf;
  for (i = 0; i < ETH_ALEN; i++) {
    ethh->h_source[i] = CONFIG.eths[eidx].haddr[i];
    ethh->h_dest[i] = dst_haddr[i];
  }
  ethh->h_proto = htons(h_proto);
   */
  return 0;
}


#endif //AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_ETH_OUT_H_
