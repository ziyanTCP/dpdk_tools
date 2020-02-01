//
// Created by ziyan on 1/18/20.
//

#ifndef MYNETWORK_LIBRARY_DPDK_INIT_H
#define MYNETWORK_LIBRARY_DPDK_INIT_H
#include <rte_ether.h>
#include <rte_ethdev.h>

#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250


static const struct rte_eth_conf port_conf_default = {
        .rxmode = {
                .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
        },
};

int port_init(uint16_t port, struct rte_mempool *mbuf_pool);
struct rte_mempool * dpdk_init(int* argc, char ***argv,struct rte_mempool **);
#endif //MYNETWORK_LIBRARY_DPDK_INIT_H
