/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** init.c
*/

#include "arpspoofing.h"

int init_arph(arp_t *arp)
{
    arp->socket_address.sll_family = AF_PACKET;
    arp->socket_address.sll_protocol = htons(ETH_P_ARP);
    arp->socket_address.sll_ifindex = arp->ifindex;
    arp->socket_address.sll_hatype = htons(ARPHRD_ETHER);
    arp->socket_address.sll_pkttype = (PACKET_BROADCAST);
    arp->socket_address.sll_halen = MAC_LEN;
    arp->socket_address.sll_addr[6] = 0x00;
    arp->socket_address.sll_addr[7] = 0x00;
}

int init_request(struct ethhdr *send_req, arphdr_t *arp_req)
{
    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REQUEST);
}

int init_reply(struct ethhdr *send_req, arphdr_t *arp_req)
{
    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REPLY);
}

arp_t *init_arp(char **av)
{
    arp_t *arp = malloc(sizeof(*arp));

    arp->sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    arp->dest = av[2];
    arp->dst = inet_addr(av[2]);
    arp->iface = av[3];

    return (arp);
}