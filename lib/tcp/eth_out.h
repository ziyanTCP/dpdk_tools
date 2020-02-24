//
// Created by Ziyan Wu on 11/15/19.
//

#ifndef AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_ETH_OUT_H_
#define AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_ETH_OUT_H_
#include <stdint.h>
#include "middleman/actors/tcp_conn/tcp_conn_actor.h"
uint8_t * EthernetOutput(struct actor_tcp_conn *mystate, uint16_t h_proto,
               int nif, unsigned char* dst_haddr, uint16_t iplen);



#endif //AUM2_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_ETH_OUT_H_
