//
// Created by ziyan on 1/13/20.
//

#include "mac.h"
#include <stdio.h>
#include <stdlib.h>
#include <rte_mbuf.h>
// convert six colon separated hex bytes string to uint64_t Ethernet MAC address
uint64_t string_to_mac(char *s) {
    unsigned char a[6];
    int rc = sscanf(s, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",
                    a + 0, a + 1, a + 2, a + 3, a + 4, a + 5);
    if(rc !=6 ){
        fprintf(stderr, "bad MAC address format. Use like: -m 0a:38:ca:f6:f3:20\n");
        exit(1);
    }

    return
            (uint64_t)(a[0]) << 40 |
            (uint64_t)(a[1]) << 32 |
            (uint64_t)(a[2]) << 24 |
            (uint64_t)(a[3]) << 16 |
            (uint64_t)(a[4]) << 8 |
            (uint64_t)(a[5]);
}

struct rte_ether_hdr* get_ethernet_header(struct rte_mbuf *pkt){
    return rte_pktmbuf_mtod_offset(pkt,char *,0);
};

struct rte_ether_addr mac_string_to_rte_ether_addr(char *mac_address){
    uint64_t DST_MAC=0ULL;
    DST_MAC=string_to_mac(mac_address)<<16;

    union {
        uint64_t as_int;
        struct rte_ether_addr as_addr;
    } dst_eth_addr; //64 bit
    dst_eth_addr.as_int=rte_cpu_to_be_64(DST_MAC); //ensure that it is big endian
    return dst_eth_addr.as_addr;
}

void send_ethernet_frame(struct rte_ether_hdr*ether_hdr,struct rte_ether_addr src_addr, struct rte_ether_addr dst_addr){

    rte_ether_addr_copy(&dst_addr,&ether_hdr->d_addr);
    rte_ether_addr_copy(&src_addr, &ether_hdr->s_addr);
    ether_hdr->ether_type = rte_cpu_to_be_16(RTE_ETHER_TYPE_IPV4);
}