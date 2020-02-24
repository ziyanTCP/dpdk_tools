//
// Created by ziyan on 1/31/20.
//

#ifndef MINIMAL_TX_IP_TCP_H
#define MINIMAL_TX_IP_TCP_H
#include "../ip.h"
#include "../mac.h"
#include "hashtable.h"
#include <rte_tcp.h>
#include <rte_ether.h>

#include "../dpdk_utility.h"
struct sender
{
    int ifidx;

    /* TCP layer send queues */
    TAILQ_HEAD (control_head, tcp_stream) control_list;
    TAILQ_HEAD (send_head, tcp_stream) send_list;
    TAILQ_HEAD (ack_head, tcp_stream) ack_list;

    int control_list_cnt;
    int send_list_cnt;
    int ack_list_cnt;
};

struct sender * CreateSender(int ifidx);

struct tcp_instance {

    struct rte_mempool* flow_pool;		/* memory pool for tcp_stream */
    struct rte_mempool* rv_pool;			/* memory pool for recv variables */
    struct rte_mempool* sv_pool;			/* memory pool for send variables */

    struct rb_manager* rbm_rcv;

    struct rte_mempool* packet_pool;

    struct hashtable *tcp_flow_table;
    uint32_t g_id;			/* id space in a thread */
    int32_t flow_cnt;		/* number of concurrent flows */


    struct sender *g_sender;
    // each sender for each ethernet port
};


struct tcp_cpu_context{
    //the context manages the cpu
    int cpu;
    struct tcp_instance* tcpInstance;
    struct dpdk_private_context* dpc;
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

struct tcp_instance* init_tcp_instance(struct tcp_instance** tcp);
struct tcp_cpu_context* init_tcp_cpu_context(struct tcp_cpu_context* cpu_ctx);
#endif //MINIMAL_TX_IP_TCP_H
