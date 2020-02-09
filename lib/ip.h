//
// Created by ziyan on 1/13/20.
//

#ifndef MYNETWORK_LIBRARY_IP_H
#define MYNETWORK_LIBRARY_IP_H

#define IP_DEFTTL  64   /* from RFC 1340. */
#define IP_VERSION 0x40
#define IP_HDRLEN  0x05 /* default IP header length == five 32-bits words. */
#define IP_VHL_DEF (IP_VERSION | IP_HDRLEN)

#define TX_PACKET_LENGTH 862

#if RTE_BYTE_ORDER == RTE_BIG_ENDIAN
#define RTE_BE_TO_CPU_16(be_16_v)  (be_16_v)
#define RTE_CPU_TO_BE_16(cpu_16_v) (cpu_16_v)
#else
#define RTE_BE_TO_CPU_16(be_16_v) \
        (uint16_t) ((((be_16_v) & 0xFF) << 8) | ((be_16_v) >> 8))
#define RTE_CPU_TO_BE_16(cpu_16_v) \
        (uint16_t) ((((cpu_16_v) & 0xFF) << 8) | ((cpu_16_v) >> 8))
#endif


#include <stdint.h>
#include <rte_ip.h>
#include <rte_mbuf.h>
#include <rte_ether.h>
#include <rte_byteorder.h>
#include <rte_ethdev.h>
uint32_t string_to_ip(char *);

struct rte_ipv4_hdr* get_ip_header(struct rte_mbuf *pkt);

char * get_ip_data(struct rte_mbuf * pkt);

uint32_t ip_string_to_rte_be32_t(char *);


uint8_t * send_ip_packet(
        struct rte_mbuf *pkt,
        rte_be32_t ip_src_addr,
        rte_be32_t ip_dst_addr,
        struct rte_ether_addr eth_src_addr,
        struct rte_ether_addr eth_dst_addr,
        uint16_t  tcp_len);

void send_ip_raw(
        struct rte_mbuf *pkt,
        char data[],
        rte_be32_t ip_src_addr,
        rte_be32_t ip_dst_addr,
        struct rte_ether_addr eth_src_addr,
        struct rte_ether_addr eth_dst_addr);

#endif //MYNETWORK_LIBRARY_IP_H
