//
// Created by ziyan on 2/4/20.
//

#include "init.h"
#include "tcp.h"
#define NUM_BINS_FLOWS 		(131072)
void init(struct tcp_instance** myinstance){
    printf("Initialization start\n");
    (*myinstance) = rte_malloc(NULL, sizeof(struct tcp_instance), 0);
    (*myinstance)->tcp_flow_table=  CreateHashtable(HashFlow, EqualFlow, NUM_BINS_FLOWS);
    (*myinstance)->flow_cnt=0;
    printf("Create tcp_flow_table done\n");


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

    printf("Initialization done\n");
}
