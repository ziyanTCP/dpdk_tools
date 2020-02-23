//
// Created by Ziyan Wu on 11/9/19.
//
#include "tcp_out.h"
#define SEND_INSTANTLY
void AddtoControlList(struct tcp_instance* tcp, struct tcp_stream *cur_stream)
{
    // TRY_SEND_BEFORE_QUEUE
    printf("AddtoControlList\n");
    int ret;
	SendControlPacket(tcp, cur_stream);
}


int SendControlPacket(struct tcp_instance* tcp, tcp_stream *cur_stream)
{
    struct tcp_send_vars *sndvar = cur_stream->sndvar;
    int ret = 0;

    if (cur_stream->state == TCP_ST_SYN_SENT) {
        /* Send SYN here */
        /*ret = SendTCPPacket(mtcp, cur_stream, cur_ts, TCP_FLAG_SYN, NULL, 0);*/

    } else if (cur_stream->state == TCP_ST_SYN_RCVD) {
/*        if (!cur_stream->sndvar->on_control_list) {

            cur_stream->sndvar->on_control_list = TRUE;
            TAILQ_INSERT_TAIL(&(tcp->g_sender->control_list), cur_stream, sndvar->control_link);
            printf("inserted ...\n");
        }*/
        printf("SendControlPacket Send SYN/ACK\n");
        struct rte_mbuf * pkt= rte_mbuf_raw_alloc( mbuf_pool);
        send_tcp_segment_raw( pkt, "",
                              cur_stream->src_addr,
                              cur_stream->dst_addr,
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

    } else if (cur_stream->state == TCP_ST_ESTABLISHED) {
        /* Send ACK here */

    }

    return ret;
}