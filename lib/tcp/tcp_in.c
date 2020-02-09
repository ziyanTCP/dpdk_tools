//
// Created by Ziyan Wu on 11/9/19.
//

#include "tcp_in.h"
#include "tcp.h"
#include "tcp_stream.h"
#include <rte_ip.h>
#include <rte_tcp.h>

#include <unistd.h> // notice this! you need it!
struct tcp_stream * CreateNewFlowHTEntry(struct tcp_instance *my_tcp, struct rte_tcp_hdr* pkt_tcp_hdr,struct rte_ipv4_hdr* pkt_ip_hdr)
{
    tcp_stream *cur_stream;
    int ret;
    if (pkt_tcp_hdr->tcp_flags==TCP_FLAG_SYN) {
        //send_ack
        printf("A SYN! \n");
        cur_stream = HandlePassiveOpen(my_tcp, pkt_ip_hdr, pkt_tcp_hdr);
        return cur_stream;
    }
    else return NULL;
}

struct tcp_stream * HandlePassiveOpen(struct tcp_instance * my_tcp, struct rte_ipv4_hdr *pkt_ip_hdr, struct rte_tcp_hdr* pkt_tcp_hdr)
{
    tcp_stream *cur_stream = NULL;
    cur_stream = CreateTCPStream(my_tcp, pkt_ip_hdr->src_addr, pkt_tcp_hdr->src_port,pkt_ip_hdr->dst_addr, pkt_tcp_hdr->dst_port );
    if (!cur_stream) {
        //TODO: TRACE_ERROR("INFO: Could not allocate tcp_stream!\n");
        return FALSE;
    }
    return cur_stream;
}
void Handle_TCP_ST_LISTEN (
        struct tcp_instance * my_tcp,
        struct tcp_stream* cur_stream,
        struct rte_tcp_hdr* pkt_tcp_hdr,
        struct rte_ether_hdr* pkt_eth_hdr,
        struct rte_mbuf* pkt){
    if (pkt_tcp_hdr->tcp_flags==TCP_FLAG_SYN) {
        cur_stream->state = TCP_ST_SYN_RCVD;
        printf("Stream %d: from TCP_ST_LISTEN to TCP_ST_SYN_RCVD\n", cur_stream->id);
        //TODO: send the response packet. P1: How and when to send. P2: How to Compose the packet
        //int ret = SendControlPacket(mystate, cur_stream, cur_ts);
        sleep(3);
        printf("Stream %d: Send SYN, ACK \n", cur_stream->id);
        char data[]="";
        send_tcp_segment_raw( pkt, data,
                              cur_stream->dst_addr,
                              cur_stream->src_addr,
                              pkt_eth_hdr->d_addr,
                              pkt_eth_hdr->s_addr,
                              rte_cpu_to_be_16(8080),
                              rte_cpu_to_be_16(8888),
                              rte_cpu_to_be_32(0),
                              rte_cpu_to_be_32(0),
                              (uint8_t)0,
                              RTE_TCP_ACK_FLAG,
                              (uint16_t) 0,
                              (uint16_t) 0);
        printf("Stream %d: SYN, ACK sent\n", cur_stream->id);
    }
    else {
        printf("Stream %d (TCP_ST_LISTEN): " "Packet without SYN.\n", cur_stream->id);
    }
}

void Handle_TCP_ST_SYN_RCVD (struct tcp_instance * my_tcp, struct tcp_stream* cur_stream, struct rte_tcp_hdr* pkt_tcp_hdr) {
    struct tcp_send_vars *sndvar = cur_stream->sndvar;
    int ret;
    if (pkt_tcp_hdr->tcp_flags==TCP_FLAG_ACK) {
        printf("Stream %d: ACK, RECEIVED\n", cur_stream->id);

        //ret = SendControlPacket(mystate, cur_stream, cur_ts);
        cur_stream->state = TCP_ST_ESTABLISHED;
        printf("Stream %d: TCP_ST_ESTABLISHED\n", cur_stream->id);
    } else {
        printf("Stream %d (TCP_ST_SYN_RCVD): No ACK.\n", cur_stream->id);
        /* retransmit SYN/ACK */
        //cur_stream->snd_nxt = sndvar->iss;
        //AddtoControlList(mtcp, cur_stream, cur_ts);
    }
}