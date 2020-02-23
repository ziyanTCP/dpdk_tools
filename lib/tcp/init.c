//
// Created by ziyan on 2/4/20.
//

#include "init.h"
#include "tcp.h"
#define NUM_BINS_FLOWS 		(131072)
#define NUM_MBUFS 8191 //not good
#define MBUF_CACHE_SIZE 250 //not good
void init(struct tcp_instance** myinstance){
    printf("Initialization start\n");
    (*myinstance) = rte_malloc(NULL, sizeof(struct tcp_instance), 0);
    (*myinstance)->tcp_flow_table=  CreateHashtable(HashFlow, EqualFlow, NUM_BINS_FLOWS);
    (*myinstance)->flow_cnt=0;
    printf("Create tcp_flow_table done\n");

    //Creates a new mempool in memory to hold the mbufs.
    unsigned nb_ports;
    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports < 2 || (nb_ports & 1))
        rte_exit(EXIT_FAILURE, "Error: number of ports must be even\n");

    (*myinstance)->packet_pool=  rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * nb_ports,
                                        MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

    printf( "************packet pool***********.\n");

    char pool_name[RTE_MEMPOOL_NAMESIZE];
    sprintf(pool_name, "rv_pool_%d", 0);

    size_t sz = RTE_ALIGN_CEIL(sizeof(struct tcp_recv_vars), RTE_CACHE_LINE_SIZE);
    (*myinstance)->rv_pool= rte_mempool_create(pool_name, MAX_CONCURRENCY, sz, 0, 0, NULL,
                                               0, NULL, 0, rte_socket_id(),
                                               MEMPOOL_F_NO_SPREAD);
    printf( "************allocate rv_pool pool***********.\n");


    sprintf(pool_name, "sv_pool%d", 0);

    sz = RTE_ALIGN_CEIL(sizeof(struct tcp_send_vars), RTE_CACHE_LINE_SIZE);
    (*myinstance)->sv_pool= rte_mempool_create(pool_name, MAX_CONCURRENCY, sz, 0, 0, NULL,
                                               0, NULL, 0, rte_socket_id(),
                                               MEMPOOL_F_NO_SPREAD);

    printf( "************allocate sv_pool pool***********.\n");

    sprintf(pool_name, "flow_pool_%d", 0);

    sz = RTE_ALIGN_CEIL(sizeof(tcp_stream), RTE_CACHE_LINE_SIZE);
    (*myinstance)->flow_pool= rte_mempool_create(pool_name, MAX_CONCURRENCY, sz, 0, 0, NULL,
                                                 0, NULL, 0, rte_socket_id(),
                                                 MEMPOOL_F_NO_SPREAD);
    printf( "************allocate flow_pool***********.\n");


    (*myinstance)->g_sender= CreateSender(0);
    printf( "************Create a sender for the instance ***********.\n");

    printf("Initialization done\n");
}
