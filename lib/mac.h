//
// Created by ziyan on 1/13/20.
//

#ifndef MYNETWORK_LIBRARY_MAC_H
#define MYNETWORK_LIBRARY_MAC_H

#include <stdint.h>
#include <rte_ether.h>
// convert six colon separated hex bytes string to uint64_t Ethernet MAC address
uint64_t string_to_mac(char *s);
struct rte_ether_hdr* get_ethernet_header(struct rte_mbuf *pkt);


struct rte_ether_addr mac_string_to_rte_ether_addr(char *);

void send_ethernet_frame(struct rte_ether_hdr*ether_hdr,struct rte_ether_addr src_addr, struct rte_ether_addr dst_addr);
#endif //MYNETWORK_LIBRARY_MAC_H
