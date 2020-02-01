//
// Created by ziyan on 1/13/20.
//

#include <stdio.h>
#include "ip.h"
#include <stdlib.h>

#include "mac.h"
uint32_t string_to_ip(char *s) {
    unsigned char a[4];
    int rc = sscanf(s, "%hhd.%hhd.%hhd.%hhd",a+0,a+1,a+2,a+3);
    if(rc != 4){
        fprintf(stderr, "bad source IP address format. Use like: -s 198.19.111.179\n");
        exit(1);
    }

    return
            (uint32_t)(a[0]) << 24 |
            (uint32_t)(a[1]) << 16 |
            (uint32_t)(a[2]) << 8 |
            (uint32_t)(a[3]);

}

uint32_t ip_string_to_rte_be32_t(char *s){
    rte_be32_t src_addr;
    uint32_t IP_ADDR;
    IP_ADDR=string_to_ip(s);
    src_addr = rte_cpu_to_be_32(IP_ADDR);
}

struct rte_ipv4_hdr* get_ip_header(struct rte_mbuf *pkt){
    return rte_pktmbuf_mtod_offset(pkt,char *, sizeof(struct rte_ether_hdr));
};

char * get_ip_data(struct rte_mbuf * pkt){
    return rte_pktmbuf_mtod_offset(pkt,char *,sizeof(struct rte_ipv4_hdr)+sizeof(struct rte_ether_hdr));
}

void send_ip_packet(struct rte_mbuf *pkt,char data[],rte_be32_t src_addr, rte_be32_t dst_addr, struct rte_ether_addr eth_src_addr, struct rte_ether_addr eth_dst_addr){

    struct rte_ether_hdr* ether_hdr= get_ethernet_header(pkt);
    //send_ethernet_frame(ether_hdr,my_addr,dst_eth_addr.as_addr);

    send_ethernet_frame(ether_hdr,eth_src_addr ,eth_dst_addr);

    uint16_t ip_pkt_data_len= strlen(data)+1;
    uint16_t ip_pkt_len = (uint16_t) (ip_pkt_data_len + sizeof(struct rte_ipv4_hdr));

    char*ip_data=get_ip_data(pkt);
    strcpy(ip_data,data);

    struct rte_ipv4_hdr * ipv4_hdr= get_ip_header(pkt);
    ipv4_hdr->version_ihl   = IP_VHL_DEF;
    ipv4_hdr->type_of_service   = 0;
    ipv4_hdr->fragment_offset = 0;
    ipv4_hdr->time_to_live   = IP_DEFTTL;
    ipv4_hdr->next_proto_id = IPPROTO_UDP;
    ipv4_hdr->packet_id = 0;
    ipv4_hdr->total_length   = RTE_CPU_TO_BE_16(ip_pkt_len);
    ipv4_hdr->src_addr = src_addr;
    ipv4_hdr->dst_addr = dst_addr;

    uint16_t *ptr16;
    uint32_t ip_cksum;
    //Compute IP header checksum.
    ptr16 = (unaligned_uint16_t*) ipv4_hdr;
    ip_cksum = 0;
    ip_cksum += ptr16[0]; ip_cksum += ptr16[1];
    ip_cksum += ptr16[2]; ip_cksum += ptr16[3];
    ip_cksum += ptr16[4];
    ip_cksum += ptr16[6]; ip_cksum += ptr16[7];
    ip_cksum += ptr16[8]; ip_cksum += ptr16[9];

    //Reduce 32 bit checksum to 16 bits and complement it.
    ip_cksum = ((ip_cksum & 0xFFFF0000) >> 16) +
               (ip_cksum & 0x0000FFFF);
    if (ip_cksum > 65535)
        ip_cksum -= 65535;
    ip_cksum = (~ip_cksum) & 0x0000FFFF;
    if (ip_cksum == 0)
        ip_cksum = 0xFFFF;
    ipv4_hdr->hdr_checksum = (uint16_t) ip_cksum;

    pkt->data_len = (uint32_t)(ip_pkt_len+ sizeof(struct rte_ether_hdr));
    pkt->nb_segs = 1;
    pkt->pkt_len = pkt->data_len;
    pkt->ol_flags = 0;

    printf("Sending packets ... [Press Ctrl+C to exit]\n");
    struct rte_mbuf *pkts_burst[1];
    // Actually send the packet
    pkts_burst[0] = pkt;
    const uint16_t nb_tx = rte_eth_tx_burst(0, 0, pkts_burst, 1);

    rte_mbuf_raw_free(pkt);
}