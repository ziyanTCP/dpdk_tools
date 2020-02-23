//
// Created by Ziyan Wu on 11/9/19.
//

#include "tcp_in.h"

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
        struct rte_ether_hdr* pkt_eth_hdr){
    if (pkt_tcp_hdr->tcp_flags==TCP_FLAG_SYN) {
        cur_stream->state = TCP_ST_SYN_RCVD;
        printf("Stream %d: from TCP_ST_LISTEN to TCP_ST_SYN_RCVD\n", cur_stream->id);
        sleep(3);
/*        printf("Stream %d: Send SYN, ACK \n", cur_stream->id);
        char data[]="";

        printf("Stream %d: SYN, ACK sent\n", cur_stream->id);*/
        AddtoControlList(my_tcp, cur_stream);
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