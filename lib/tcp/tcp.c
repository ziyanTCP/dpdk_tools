//
// Created by ziyan on 1/31/20.
//

#include "tcp.h"
#include "../mac.h"
#include <rte_tcp.h>
#include <rte_ether.h>
struct rte_tcp_hdr* get_tcp_data(struct rte_mbuf *pkt){
    return rte_pktmbuf_mtod_offset(pkt,char *, sizeof(struct rte_ether_hdr)+sizeof(struct rte_ipv4_hdr)+sizeof(struct rte_tcp_hdr));
};
struct rte_ipv4_hdr* get_tcp_header(struct rte_mbuf *pkt){
    return rte_pktmbuf_mtod_offset(pkt,char *, sizeof(struct rte_ether_hdr)+sizeof(struct rte_ipv4_hdr));
};

void send_tcp_segment(
        struct rte_mbuf *pkt,
        char *data,
        rte_be32_t ip_src_addr,
        rte_be32_t ip_dst_addr,
        struct rte_ether_addr eth_src_addr,
        struct rte_ether_addr eth_dst_addr,
        rte_be16_t src_port, /**< TCP source port. */
        rte_be16_t dst_port, /**< TCP destination port. */
        rte_be32_t sent_seq, /**< TX data sequence number. */
        rte_be32_t recv_ack, /**< RX data acknowledgment sequence number. */
        uint8_t  data_off, /**< Data offset. */
        uint8_t  tcp_flags,  /**< TCP flags */
        rte_be16_t rx_win,  /**< RX flow control window. */
        rte_be16_t tcp_urp)  /**< TCP urgent pointer, if any. */
{

    struct rte_ipv4_hdr * ipv4_hdr= get_ip_header(pkt);
    struct rte_tcp_hdr * tcp_hdr= get_tcp_header(pkt);


    uint16_t tcp_pkt_data_len= strlen(data)+1;
    uint16_t tcp_pkt_len = (uint16_t) (tcp_pkt_data_len + sizeof(struct rte_tcp_hdr));
    char*tcp_data=get_tcp_data(pkt);
    strcpy(tcp_data,data);

    tcp_hdr->src_port=src_port;
    tcp_hdr->dst_port=dst_port;
    tcp_hdr->sent_seq=sent_seq;
    tcp_hdr->recv_ack=recv_ack;
    tcp_hdr->data_off=data_off;
    tcp_hdr->tcp_flags=tcp_flags;
    tcp_hdr->rx_win=rx_win;
    tcp_hdr->tcp_urp=tcp_urp;

    send_ip_packet(pkt,ip_src_addr,ip_dst_addr,eth_src_addr,eth_dst_addr,tcp_pkt_len);
}

void send_tcp_segment_raw(
        struct rte_mbuf *pkt,
        char *data,
        rte_be32_t ip_src_addr,
        rte_be32_t ip_dst_addr,
        struct rte_ether_addr eth_src_addr,
        struct rte_ether_addr eth_dst_addr,
        rte_be16_t src_port, /**< TCP source port. */
        rte_be16_t dst_port, /**< TCP destination port. */
        rte_be32_t sent_seq, /**< TX data sequence number. */
        rte_be32_t recv_ack, /**< RX data acknowledgment sequence number. */
        uint8_t  data_off, /**< Data offset. */
        uint8_t  tcp_flags,  /**< TCP flags */
        rte_be16_t rx_win,  /**< RX flow control window. */
        rte_be16_t tcp_urp)  /**< TCP urgent pointer, if any. */
{

    struct rte_ipv4_hdr * ipv4_hdr= get_ip_header(pkt);
    struct rte_tcp_hdr * tcp_hdr= get_tcp_header(pkt);


    uint16_t tcp_pkt_data_len= strlen(data)+1;
    uint16_t tcp_pkt_len = (uint16_t) (tcp_pkt_data_len + sizeof(struct rte_tcp_hdr));
    char*tcp_data=get_tcp_data(pkt);
    strcpy(tcp_data,data);

    tcp_hdr->src_port=src_port;
    tcp_hdr->dst_port=dst_port;
    tcp_hdr->sent_seq=sent_seq;
    tcp_hdr->recv_ack=recv_ack;
    tcp_hdr->data_off=data_off;
    tcp_hdr->tcp_flags=tcp_flags;
    tcp_hdr->rx_win=rx_win;
    tcp_hdr->tcp_urp=tcp_urp;

    send_ip_packet(pkt,ip_src_addr,ip_dst_addr,eth_src_addr,eth_dst_addr,tcp_pkt_len);


    pkt->data_len = (uint32_t)(sizeof(struct rte_ipv4_hdr)+ sizeof(struct rte_ether_hdr)+tcp_pkt_len );
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