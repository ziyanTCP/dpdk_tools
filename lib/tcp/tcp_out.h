//
// Created by Ziyan Wu on 11/9/19.
//

#ifndef AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_OUT_H_
#define AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_OUT_H_

#include "../dpdk_utility.h"
void AddtoControlList(struct tcp_instance* tcp, struct tcp_stream *cur_stream);
int SendControlPacket(struct tcp_instance* tcp, struct tcp_stream *cur_stream);


#endif //AUM_COORDINATOR_INCLUDE_MIDDLEMAN_ACTORS_TCP_CONN_TCP_OUT_H_
