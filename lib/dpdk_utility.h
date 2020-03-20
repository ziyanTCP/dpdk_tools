//
// Created by ziyan on 2/4/20.
//

#ifndef MYNETWORK_LIBRARY_DPDK_UTILITY_H
#define MYNETWORK_LIBRARY_DPDK_UTILITY_H

#include <stddef.h>
#include <rte_mbuf_core.h>
#include <rte_byteorder.h>
#include <rte_ether.h>

#include <rte_tcp.h>
#include <rte_ip.h>
#include "/home/ziyan/Dropbox/mylibrary/ziyan_tcpstack/lib/ip.h"
#include "/home/ziyan/Dropbox/mylibrary/ziyan_tcpstack/lib/mac.h"
#include "/home/ziyan/Dropbox/mylibrary/ziyan_tcpstack/lib/dpdk_init.h"
#include "/home/ziyan/Dropbox/mylibrary/ziyan_tcpstack/lib/tcp/tcp.h"


#include "tcp/init.h"
#include "tcp/tcp_action.h"
#include "tcp/tcp_stream.h"
#include "tcp/tcp_in.h"
#include "tcp/tcp_out.h"
#include "tcp/dpdk_module.h"
#include "tcp/dpdk_module.h"
#include "tcp/tcp_ring_buffer.h"
#include "tcp/tcp_rb_frag_queue.h"
void rx_packets(struct rte_mbuf** pkt);
void DumpHex(const void* data, size_t size);
void analyze_TCP_packet(struct rte_mbuf *pkt);

void menu(struct rte_mbuf *pkt, struct rte_mbuf *recv_pkt, char data[],rte_be32_t ip_src_addr, rte_be32_t ip_dst_addr,struct rte_ether_addr my_addr,struct rte_ether_addr eth_dst_addr);
// recieve one packet
//void rx_packets(struct rte_mbuf* pkt);
#endif //MYNETWORK_LIBRARY_DPDK_UTILITY_H