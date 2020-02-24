//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_IP_OUT_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_IP_OUT_H_
#include <stdint.h>
#include "middleman/actors/tcp_conn/tcp_stream.h"
/*
uint8_t * IPOutputStandalone(struct actor_tcp_conn *mystate, uint8_t protocol,
                   uint16_t ip_id, uint32_t saddr, uint32_t daddr, uint16_t payloadlen);
*/


uint8_t * IPOutput(struct actor_tcp_conn *mystate, tcp_stream *stream, uint16_t tcplen);


#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_IP_OUT_H_
