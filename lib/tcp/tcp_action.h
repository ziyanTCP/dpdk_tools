//
// Created by ziyan on 2/4/20.
//

#ifndef MINIMAL_RX_TCP_ACTION_H
#define MINIMAL_RX_TCP_ACTION_H

#include <stdio.h>
#include "../dpdk_utility.h"
void tcp_action(struct tcp_instance* my_tcp, struct rte_mbuf* recv_pkt,struct rte_mbuf* pkt);
#endif //MINIMAL_RX_TCP_ACTION_H
