//
// Created by ziyan on 2/4/20.
//

#include "dpdk_utility.h"
#include "stdio.h"
#include <rte_mbuf_core.h>
#include "rte_tcp.h"
#include "tcp/tcp.h"
void DumpHex(const void* data, size_t size) {
    char ascii[17];
    size_t i, j;
    ascii[16] = '\0';
    for (i = 0; i < size; ++i) {
        printf("%02X ", ((const unsigned char*)data)[i]);
        if (((const unsigned char*)data)[i] >= ' ' && ((const unsigned char*)data)[i] <= '~') {
            ascii[i % 16] = ((const unsigned char*)data)[i];
        } else {
            ascii[i % 16] = '.';
        }
        if ((i+1) % 8 == 0 || i+1 == size) {
            printf(" ");
            if ((i+1) % 16 == 0) {
                printf("|  %s \n", ascii);
            } else if (i+1 == size) {
                ascii[(i+1) % 16] = '\0';
                if ((i+1) % 16 <= 8) {
                    printf(" ");
                }
                for (j = (i+1) % 16; j < 16; ++j) {
                    printf("   ");
                }
                printf("|  %s \n", ascii);
            }
        }
    }
}

void analyze_TCP_packet(struct rte_mbuf *pkt) {

    struct rte_ipv4_hdr *pkt_ip_hdr;  /**< IP header of transmitted packets. */
    struct rte_udp_hdr *pkt_udp_hdr; /**< UDP header of transmitted packets. */
    struct rte_ether_hdr *pkt_eth_hdr;
    struct rte_tcp_hdr *pkt_tcp_hdr;

    pkt_eth_hdr = rte_pktmbuf_mtod(pkt, struct rte_ether_hdr *);
    pkt_ip_hdr = rte_pktmbuf_mtod_offset(pkt, struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));
    pkt_tcp_hdr = rte_pktmbuf_mtod_offset(pkt, struct rte_tcp_hdr *,
    sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));

    switch (pkt_ip_hdr->next_proto_id) {
        case IPPROTO_TCP:
            printf("TCP ");

            switch (pkt_tcp_hdr->tcp_flags) {
                case RTE_TCP_SYN_FLAG:
                    printf("S ");
                    break;

                case RTE_TCP_CWR_FLAG:
                    printf("CWR ");
                    break;

                case RTE_TCP_ACK_FLAG:
                    printf("ACK ");
                    break;

                case RTE_TCP_ACK_FLAG + RTE_TCP_SYN_FLAG:
                    printf("SA ");
                    break;
                default:
                    printf("protocol %d ", pkt_ip_hdr->next_proto_id);
            }

            char *data = get_tcp_data(pkt);
            printf("%s\n", data);

            DumpHex(rte_pktmbuf_mtod(pkt, char *), pkt->pkt_len);
    }
}

void rx_packets(struct rte_mbuf** pkt)  // you want to change the value of *p, so it is **p
{
    uint16_t port;
    int i;
    struct rte_mbuf *bufs[32];
    /* Run until the application is quit or killed. */
    while(1) {
        RTE_ETH_FOREACH_DEV(port) {

            const uint16_t nb_rx = rte_eth_rx_burst(port, 0,
                                                    bufs, 32);
            *pkt= bufs[0];
            if (unlikely(nb_rx == 0))
                continue;

            return;
            //printf("received %d packets:\n",nb_rx);

            //DumpHex(rte_pktmbuf_mtod(bufs[i],char s*),bufs[i]->pkt_len);


        }
    }
}

void menu(struct rte_mbuf *pkt, struct rte_mbuf* recv_pkt, char data[],rte_be32_t ip_src_addr, rte_be32_t ip_dst_addr,struct rte_ether_addr my_addr,struct rte_ether_addr eth_dst_addr){
        puts ("Enter Options."
              "\n1. Syn packet"
              "\n2. Ack packet"
              "\n3. Syn Ack packet"
              "\n4. Establish a connection through a three-way handshake"
              "\n5. send data"
              "\n ");

        char c;
        c=getchar();

        switch(c){
            case '1':
                send_tcp_segment_raw( pkt, data,
                                      ip_src_addr,
                                      ip_dst_addr,
                                      my_addr,
                                      eth_dst_addr,
                                      rte_cpu_to_be_16(8888),
                                      rte_cpu_to_be_16(8080),
                                      rte_cpu_to_be_32(0),
                                      rte_cpu_to_be_32(0),
                                      (uint8_t)0,
                                      RTE_TCP_SYN_FLAG,
                                      (uint16_t) 0,
                                      (uint16_t) 0);
                break;

            case '2':
                send_tcp_segment_raw( pkt, data,
                                      ip_src_addr,
                                      ip_dst_addr,
                                      my_addr,
                                      eth_dst_addr,
                                      rte_cpu_to_be_16(8888),
                                      rte_cpu_to_be_16(8080),
                                      rte_cpu_to_be_32(0),
                                      rte_cpu_to_be_32(0),
                                      (uint8_t)0,
                                      RTE_TCP_ACK_FLAG,
                                      (uint16_t) 0,
                                      (uint16_t) 0);
                break;

            case '3':
                send_tcp_segment_raw( pkt, data,
                                      ip_src_addr,
                                      ip_dst_addr,
                                      my_addr,
                                      eth_dst_addr,
                                      rte_cpu_to_be_16(8888),
                                      rte_cpu_to_be_16(8080),
                                      rte_cpu_to_be_32(0),
                                      rte_cpu_to_be_32(0),
                                      (uint8_t)0,
                                      RTE_TCP_ACK_FLAG + RTE_TCP_SYN_FLAG,
                                      (uint16_t) 0,
                                      (uint16_t) 0);
                break;
            case '4':
                send_tcp_segment_raw( pkt, data,
                                      ip_src_addr,
                                      ip_dst_addr,
                                      my_addr,
                                      eth_dst_addr,
                                      rte_cpu_to_be_16(8888),
                                      rte_cpu_to_be_16(8080),
                                      rte_cpu_to_be_32(0),
                                      rte_cpu_to_be_32(0),
                                      (uint8_t)0,
                                      RTE_TCP_SYN_FLAG,
                                      (uint16_t) 0,
                                      (uint16_t) 0);
                printf("waiting for ACK\n");
                rx_packets(&recv_pkt);
                printf("get the ACK, send ACK\n");
                send_tcp_segment_raw( pkt, data,
                                      ip_src_addr,
                                      ip_dst_addr,
                                      my_addr,
                                      eth_dst_addr,
                                      rte_cpu_to_be_16(8888),
                                      rte_cpu_to_be_16(8080),
                                      rte_cpu_to_be_32(0),
                                      rte_cpu_to_be_32(0),
                                      (uint8_t)0,
                                      RTE_TCP_ACK_FLAG,
                                      (uint16_t) 0,
                                      (uint16_t) 0);
                printf("ACK sent\n");
                analyze_TCP_packet(recv_pkt);
                break;
            case '5':
                send_tcp_segment_raw( pkt, "aaaaaaaaaaaa",
                                      ip_src_addr,
                                      ip_dst_addr,
                                      my_addr,
                                      eth_dst_addr,
                                      rte_cpu_to_be_16(8888),
                                      rte_cpu_to_be_16(8080),
                                      rte_cpu_to_be_32(0),
                                      rte_cpu_to_be_32(0),
                                      (uint8_t)0,
                                      NULL,
                                      (uint16_t) 0,
                                      (uint16_t) 0);
                break;

        };
}