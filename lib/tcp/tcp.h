//
// Created by ziyan on 1/31/20.
//

#ifndef MINIMAL_TX_IP_TCP_H
#define MINIMAL_TX_IP_TCP_H
#include "../ip.h"
#include "../mac.h"
#include "hashtable.h"

struct tcp_instance {

    struct rte_mempool* flow_pool;		/* memory pool for tcp_stream */
    struct rte_mempool* rv_pool;			/* memory pool for recv variables */
    struct rte_mempool* sv_pool;			/* memory pool for send variables */


    struct hashtable *tcp_flow_table;
    uint32_t g_id;			/* id space in a thread */
    int32_t flow_cnt;		/* number of concurrent flows */
};

struct rte_tcp_hdr* get_tcp_data(struct rte_mbuf *pkt);
struct rte_ipv4_hdr* get_tcp_header(struct rte_mbuf *pkt);
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
        rte_be16_t tcp_urp)  /**< TCP urgent pointer, if any. */;

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
        rte_be16_t tcp_urp)  /**< TCP urgent pointer, if any. */;
#endif //MINIMAL_TX_IP_TCP_H
