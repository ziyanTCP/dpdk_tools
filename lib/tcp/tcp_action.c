//
// Created by ziyan on 2/4/20.
//

#include "tcp_action.h"
#include "stdio.h"
#include "tcp_in.h"
void tcp_action(struct tcp_instance* my_tcp,struct rte_mbuf* recv_pkt){
    printf("**********TCP action starts:**********\n");
    struct tcp_stream s_stream;
    struct tcp_stream *cur_stream = NULL;

    struct rte_ipv4_hdr *pkt_ip_hdr;  /**< IP header of transmitted packets. */
    struct rte_udp_hdr *pkt_udp_hdr; /**< UDP header of transmitted packets. */
    struct rte_ether_hdr *pkt_eth_hdr;
    struct rte_tcp_hdr *pkt_tcp_hdr;

    pkt_eth_hdr = rte_pktmbuf_mtod(recv_pkt, struct rte_ether_hdr *);
    pkt_ip_hdr = rte_pktmbuf_mtod_offset(recv_pkt, struct rte_ipv4_hdr *, sizeof(struct rte_ether_hdr));
    pkt_tcp_hdr = rte_pktmbuf_mtod_offset(recv_pkt, struct rte_tcp_hdr *, sizeof(struct rte_ether_hdr) + sizeof(struct rte_ipv4_hdr));


    get_stream(&s_stream,recv_pkt);

    printf("searching the flow in flow table\n");
    cur_stream = StreamHTSearch(my_tcp->tcp_flow_table, &s_stream);
    if (!cur_stream){
        printf("not found! Creating...\n");
        cur_stream = CreateNewFlowHTEntry(my_tcp,pkt_tcp_hdr,pkt_ip_hdr);
    }
    else{
        printf("%d.%d.%d.%d:%d ---> %d.%d.%d.%d:%d already in the flow table\n",
               pkt_ip_hdr->src_addr & 0xFF,
               pkt_ip_hdr->src_addr >> 8& 0xFF,
               pkt_ip_hdr->src_addr >> 16& 0xFF,
               pkt_ip_hdr->src_addr >> 24& 0xFF,
               ntohs(pkt_tcp_hdr->src_port),
               pkt_ip_hdr->dst_addr & 0xFF,
               pkt_ip_hdr->dst_addr >> 8& 0xFF,
               pkt_ip_hdr->dst_addr >> 16& 0xFF,
               pkt_ip_hdr->dst_addr >> 24& 0xFF,
               ntohs(pkt_tcp_hdr->dst_port));
    }
    analyze_TCP_packet(recv_pkt);
    printf("Entering the state machine for the flow\n");
    switch (cur_stream->state) {
        case TCP_ST_LISTEN:
            printf("State: TCP_ST_LISTEN\n");
            printf("Handling TCP_ST_LISTEN\n");
            Handle_TCP_ST_LISTEN(my_tcp,  cur_stream, pkt_tcp_hdr,pkt_eth_hdr);
            break;
        case TCP_ST_SYN_RCVD:
            printf("State: TCP_ST_SYN_RCVD\n");
            Handle_TCP_ST_SYN_RCVD(my_tcp,  cur_stream, pkt_tcp_hdr);
            break;

        case TCP_ST_ESTABLISHED:
            printf("State: TCP_ST_ESTABLISHED\n");

            break;

        case TCP_ST_LAST_ACK:
            printf("State: TCP_ST_LAST_ACK\n");
            break;
    }
    printf("**********TCP action ends**********\n\n");
}