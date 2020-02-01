//
// Created by ziyan on 1/31/20.
//

#ifndef MYNETWORK_LIBRARY_TEST_MINIMAL_IP_SEND_H
#define MYNETWORK_LIBRARY_TEST_MINIMAL_IP_SEND_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

#include <rte_memory.h>
#include <rte_eal.h>
#include <rte_lcore.h>
#include <rte_ethdev.h>
#include <rte_udp.h>
#include <rte_ip.h>

#include "/home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/ip.h"
#include "/home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/mac.h"
#include "/home/ziyan/Dropbox/mylibrary/dpdk_tools/lib/dpdk_init.h"


void test_minimal_ip_send(int argc, char ** argv){
    int mac_flag=0,ip_src_flag=0,ip_dst_flag=0;


    rte_be32_t src_addr, dst_addr;
    struct rte_ether_addr my_addr; // SRC MAC address of NIC
    struct rte_ether_addr eth_dst_addr;
    struct rte_mempool* mbuf_pool;
    dpdk_init(&argc,&argv,&mbuf_pool);

    int c=0;
    while ((c = getopt(argc, argv, "m:s:d:h")) != -1)
        switch(c) {
            case 'm':
                eth_dst_addr=mac_string_to_rte_ether_addr(optarg);
                mac_flag=1;
                break;
            case 's':
                src_addr= ip_string_to_rte_be32_t(optarg);
                ip_src_flag=1;
                break;
            case 'd':
                dst_addr = ip_string_to_rte_be32_t(optarg);
                ip_dst_flag=1;
                break;
            case 'h':
                printf("usage -- -m [dst MAC] -s [src IP] -d [dst IP]\n");
                exit(0);
        }

    if(mac_flag==0) {
        fprintf(stderr, "missing -m for destination MAC adress\n");
        exit(1);
    }
    if(ip_src_flag==0) {
        fprintf(stderr, "missing -s for IP source adress\n");
        exit(1);
    }
    if(ip_dst_flag==0) {
        fprintf(stderr, "missing -d for IP destination adress\n");
        exit(1);
    }


    struct rte_mbuf * pkt= rte_mbuf_raw_alloc(mbuf_pool);
    char data[]="hello world my name is ziyan wu i am a phd student at UMN I am a first year Ph.D student";

    while(1){
        send_ip_packet(pkt,data,src_addr,dst_addr,my_addr,eth_dst_addr);
    }
}
#endif //MYNETWORK_LIBRARY_TEST_MINIMAL_IP_SEND_H
