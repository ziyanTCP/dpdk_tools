//
// Created by ziyan on 2/14/20.
//

#ifndef MYNETWORK_LIBRARY_DPDK_MODULE_H
#define MYNETWORK_LIBRARY_DPDK_MODULE_H

#undef RTE_MAX_ETHPORTS
#define RTE_MAX_ETHPORTS 32
#define MAX_PKT_BURST 64
#include <rte_mbuf.h>
#include "tcp.h"
#include "../dpdk_utility.h"
#include "../dpdk_macro.h"

#ifndef MAX_CPUS
#define MAX_CPUS 1 // set 1 for now
#endif

#define NUM_MBUFS 8191
#define MBUF_CACHE_SIZE 250


static const struct rte_eth_conf port_conf_default = {
        .rxmode = {
                .max_rx_pkt_len = RTE_ETHER_MAX_LEN,
        },
};

int port_init(uint16_t port, struct rte_mempool *mbuf_pool);
struct rte_mempool * dpdk_init(int* argc, char ***argv);

struct mbuf_table {
    uint16_t len; /* length of queued packets */
    struct rte_mbuf *m_table[MAX_PKT_BURST];
};

struct dpdk_private_context {
    struct mbuf_table rmbufs[RTE_MAX_ETHPORTS];
    struct mbuf_table wmbufs[RTE_MAX_ETHPORTS];
    struct rte_mempool *pktmbuf_pool;
    struct rte_mbuf *pkts_burst[MAX_PKT_BURST];
} /*__rte_cache_aligned;*/ ;

void init_dpdk_private_context(struct tcp_cpu_context *ctxt);

#endif //MYNETWORK_LIBRARY_DPDK_MODULE_H
