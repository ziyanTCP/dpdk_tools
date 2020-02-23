//
// Created by ziyan on 1/31/20.
//

#include "tcp.h"

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


struct sender * CreateSender(int ifidx)
{
    struct sender *s;

    s = (struct sender *)calloc(1, sizeof(struct sender));
    if (!s) {
        return NULL;
    }

    s->ifidx = ifidx;

    TAILQ_INIT(&s->control_list);
    printf("Init contorl_list\n");
    TAILQ_INIT(&s->send_list);
    printf("Init send list\n");
    TAILQ_INIT(&s->ack_list);
    printf("Init ack list\n");

    s->control_list_cnt = 0;
    s->send_list_cnt = 0;
    s->ack_list_cnt = 0;

    return s;
}

struct tcp_instance* init_tcp_instance(struct tcp_instance** tcp){

    printf("Initialization of tcp instance starts\n");
    (*tcp) = calloc(1, sizeof(tcp));
    (*tcp)->tcp_flow_table=  CreateHashtable(HashFlow, EqualFlow, NUM_BINS_FLOWS);
    (*tcp)->flow_cnt=0;
    printf("Create tcp_flow_table done\n");

    //Creates a new mempool in memory to hold the mbufs.
    unsigned nb_ports;
    nb_ports = rte_eth_dev_count_avail();
    if (nb_ports < 2 || (nb_ports & 1))
        rte_exit(EXIT_FAILURE, "Error: number of ports must be even\n");

    (*tcp)->packet_pool=  rte_pktmbuf_pool_create("MBUF_POOL", NUM_MBUFS * nb_ports,
                                                         MBUF_CACHE_SIZE, 0, RTE_MBUF_DEFAULT_BUF_SIZE, rte_socket_id());

    printf( "************packet pool***********.\n");

    char pool_name[RTE_MEMPOOL_NAMESIZE];
    sprintf(pool_name, "rv_pool_%d", 0);

    size_t sz = RTE_ALIGN_CEIL(sizeof(struct tcp_recv_vars), RTE_CACHE_LINE_SIZE);
    (*tcp)->rv_pool= rte_mempool_create(pool_name, MAX_CONCURRENCY, sz, 0, 0, NULL,
                                               0, NULL, 0, rte_socket_id(),
                                               MEMPOOL_F_NO_SPREAD);
    printf( "************allocate rv_pool pool***********.\n");

    sprintf(pool_name, "sv_pool%d", 0);

    sz = RTE_ALIGN_CEIL(sizeof(struct tcp_send_vars), RTE_CACHE_LINE_SIZE);
    (*tcp)->sv_pool= rte_mempool_create(pool_name, MAX_CONCURRENCY, sz, 0, 0, NULL,
                                               0, NULL, 0, rte_socket_id(),
                                               MEMPOOL_F_NO_SPREAD);

    printf( "************allocate sv_pool pool***********.\n");

    sprintf(pool_name, "flow_pool_%d", 0);

    sz = RTE_ALIGN_CEIL(sizeof(tcp_stream), RTE_CACHE_LINE_SIZE);
    (*tcp)->flow_pool= rte_mempool_create(pool_name, MAX_CONCURRENCY, sz, 0, 0, NULL,
                                                 0, NULL, 0, rte_socket_id(),
                                                 MEMPOOL_F_NO_SPREAD);
    printf( "************allocate flow_pool***********.\n");

    (*tcp)->g_sender= CreateSender(0);
    printf( "************Create a sender for the instance ***********.\n");
    printf("Initialization of tcp instance done\n");
}

struct tcp_cpu_context* init_tcp_cpu_context(struct tcp_cpu_context* cpu_ctx){
    //resources are managed under one CPU
    //TODO: log function
    printf("Initialization of CPU context starts\n");
    cpu_ctx->cpu=0;//how to get the current cpu?

    init_tcp_instance(&cpu_ctx->tcpInstance);
    init_dpdk_private_context(cpu_ctx);

    printf("Initialization of CPU context done\n");
    return cpu_ctx;
}