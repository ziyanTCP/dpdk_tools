//
// Created by ziyan on 2/14/20.
//

#include "dpdk_module.h"

static struct rte_mempool *pktmbuf_pool = NULL;

void init_dpdk_private_context(struct tcp_cpu_context *ctxt) {
    printf("Initialization of DPDK private context starts\n");
    int i, j;
    char mempool_name[RTE_MEMPOOL_NAMESIZE];

    /* create and initialize private I/O module context */
    ctxt->dpc = calloc(1, sizeof(struct dpdk_private_context));
    printf("Create DPDK private context\n");

    ctxt->dpc->pktmbuf_pool=pktmbuf_pool;

    int num_devices_attached = 2;
    for (j = 0; j < num_devices_attached; j++) {
        for (i = 0; i < MAX_PKT_BURST; i++) {
            ctxt->dpc->wmbufs[j].m_table[i] = rte_pktmbuf_alloc(ctxt->dpc->pktmbuf_pool);
            if (ctxt->dpc->wmbufs[j].m_table[i] == NULL) {
                printf("Failed to allocate %d:wmbuf[%d] on device %d!\n",
                       ctxt->cpu, i, j);
                exit(EXIT_FAILURE);
            }
        }
    }

    printf("Initialization of DPDK private context done\n");
}


void dpdk_load_module(void){

}


int port_init(uint16_t port, struct rte_mempool *mbuf_pool)
{
    rte_log_set_level(RTE_LOGTYPE_EAL,RTE_LOG_DEBUG);
    struct rte_eth_conf port_conf = port_conf_default;
    const uint16_t rx_rings = 1, tx_rings = 1;
    uint16_t nb_rxd = RX_RING_SIZE;
    uint16_t nb_txd = TX_RING_SIZE;
    int retval;
    uint16_t q;
    struct rte_eth_txconf txconf;
    struct rte_eth_dev_info dev_info;
    rte_eth_dev_info_get(port, &dev_info);
    if (dev_info.tx_offload_capa & DEV_TX_OFFLOAD_MBUF_FAST_FREE)
        port_conf.txmode.offloads |=
                DEV_TX_OFFLOAD_MBUF_FAST_FREE;

    txconf = dev_info.default_txconf;
    txconf.offloads = port_conf.txmode.offloads;

    if (!rte_eth_dev_is_valid_port(port))
        return -1;

    /* Configure the Ethernet device. */
    retval = rte_eth_dev_configure(port, rx_rings, tx_rings, &port_conf);
    if (retval != 0)
        return retval;

    retval = rte_eth_dev_adjust_nb_rx_tx_desc(port, &nb_rxd, &nb_txd);
    if (retval != 0)
        return retval;
    //rte_log(RTE_LOG_EMERG,RTE_LOGTYPE_EAL, "Allocate and set up 1 TX queue");
    //Allocate and set up 1 TX queue
    for (q = 0; q < tx_rings; q++) {
        retval = rte_eth_tx_queue_setup(port, q, nb_txd,
                                        rte_eth_dev_socket_id(port), &txconf);
        if (retval < 0)
            return retval;
    }

    /* Allocate and set up 1 RX queue per Ethernet port. */
    for (q = 0; q < rx_rings; q++) {
        retval = rte_eth_rx_queue_setup(port, q, nb_rxd,
                                        rte_eth_dev_socket_id(port), NULL, mbuf_pool);
        if (retval < 0)
            return retval;
    }

    /* Start the Ethernet port. */
    retval = rte_eth_dev_start(port);
    if (retval < 0)
        return retval;

    /* Display the port MAC address. */
    struct rte_ether_addr addr;
    rte_eth_macaddr_get(port, &addr);
    printf("Port %u MAC: %02" PRIx8 " %02" PRIx8 " %02" PRIx8
           " %02" PRIx8 " %02" PRIx8 " %02" PRIx8 "\n",
           port,
           addr.addr_bytes[0], addr.addr_bytes[1],
           addr.addr_bytes[2], addr.addr_bytes[3],
           addr.addr_bytes[4], addr.addr_bytes[5]);

    /* Enable RX in promiscuous mode for the Ethernet device. */
    rte_eth_promiscuous_enable(port);

    return 0;
}

struct rte_mempool * dpdk_init(int* argc, char ***argv){
    // TODO Can I move this part to DPDK initialization?
    unsigned nb_ports;
    uint16_t portid;

    /* Initialize the Environment Abstraction Layer (EAL). */
    int ret = rte_eal_init(*argc, *argv);
    if (ret < 0)
        rte_exit(EXIT_FAILURE, "Error with EAL initialization\n");

    *argc -= ret;
    *argv += ret;

    /* Check that there is an even number of ports to send/receive on. */
    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports < 2 || (nb_ports & 1))
        rte_exit(EXIT_FAILURE, "Error: number of ports must be even\n");

    //Creates a new mempool in memory to hold the mbufs.
    pktmbuf_pool = rte_pktmbuf_pool_create("MBUF_POOL rec", NUM_MBUFS * nb_ports,
                                         MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());
/*
    if (mbuf_pool == NULL)
        rte_exit(EXIT_FAILURE, "Cannot create mbuf pool\n");*/

    /* Initialize all ports. */
    RTE_ETH_FOREACH_DEV(portid)
        if (port_init(portid, pktmbuf_pool) != 0)
            rte_exit(EXIT_FAILURE, "Cannot init port %"PRIu16 "\n",
                     portid);

    return pktmbuf_pool;
}