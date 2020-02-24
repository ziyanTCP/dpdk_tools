//
// Created by Ziyan Wu on 11/9/19.
//

#include "tcp_stream.h"
#include "tcp_in.h"
struct tcp_stream * CreateTCPStream(struct tcp_instance * my_tcp, rte_be32_t saddr, rte_be16_t sport, rte_be32_t daddr, rte_be16_t dport)
{
  tcp_stream *stream = NULL;

  int rc= rte_mempool_get(my_tcp->flow_pool, (void **)&stream);
  if (rc != 0)
    return NULL;


  memset(stream, 0, sizeof(tcp_stream)); // all set to 0

  rc= rte_mempool_get(my_tcp->rv_pool, (void **)&stream->rcvvar);
  rc= rte_mempool_get(my_tcp->sv_pool, (void **)&stream->sndvar);

  memset(stream->rcvvar, 0, sizeof(struct tcp_recv_vars)); // all set to 0
  memset(stream->sndvar, 0, sizeof(struct tcp_send_vars)); // all set to 0

  //stream->id = my_tcp->g_id++;
  stream->src_addr = saddr;
  stream->src_port = sport;
  stream->dst_addr = daddr;
  stream->dst_port = dport;

  int ret = StreamHTInsert(my_tcp->tcp_flow_table, stream);

  stream->rcvvar->irs = 0;

  stream->on_hash_table = TRUE;
  stream->state = TCP_ST_LISTEN;

  my_tcp->flow_cnt++;

/*  if (socket) {
    stream->socket = socket;
    socket->stream = stream;
  }*/

  uint8_t * sa = (uint8_t *)&stream->src_addr;
  uint8_t * da = (uint8_t *)&stream->dst_addr;
  printf("CREATED NEW TCP STREAM %d: "
               "%u.%u.%u.%u(%d) -> %u.%u.%u.%u(%d)\n", stream->id,
               sa[0], sa[1], sa[2], sa[3], ntohs(stream->src_port),
               da[0], da[1], da[2], da[3], ntohs(stream->dst_port));
  return stream;
}

void DestroyTCPStream(struct tcp_instance * my_tcp, tcp_stream *stream){
  // TODO: free memory
  StreamHTRemove(my_tcp->tcp_flow_table, stream);
  stream->on_hash_table = FALSE;
  my_tcp->flow_cnt--;
  return;
}

void get_stream(struct tcp_stream * stream, struct rte_mbuf* pkt){
    struct rte_tcp_hdr * tcp_hdr= get_tcp_header(pkt);
    struct rte_ipv4_hdr * ip_hdr= get_ip_header(pkt);
    stream->src_addr= ip_hdr->src_addr;
    stream->dst_addr= ip_hdr->dst_addr;
    stream->src_port=tcp_hdr->src_port;
    stream->dst_port= tcp_hdr->dst_port;
}