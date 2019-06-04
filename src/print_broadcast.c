/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** flags.c
*/

#include "arpspoofing.h"

int init_arph3(arp_t *arp)
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

int set_header3(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req)
{
    memset(arp->buffer, 0, sizeof(arp->buffer));
    memset(send_req->h_dest, 0xff, MAC_LEN);
    memset(arp_req->dest_mac, 0xff, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);
}

int init_req3(struct ethhdr *send_req, arphdr_t *arp_req)
{
    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REQUEST);
}

int loop_broadcast(arp_t *arp)
{
    int i = 0;

    while (i < 42) {
        if ((arp->buffer[i] & 0xff) >= 0 && (arp->buffer[i] & 0xff) <= 8)
            printf("0");
        printf("%x", arp->buffer[i] & 0xff);
        if (i < 41)
            printf(" ");
        i++;
    }
    printf("\n");
}

int print_broadcast(char **av)
{
    arp_t *arp = init_arp(av);
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);

    ifr_getter2(arp);
    init_arph3(arp);
    set_header3(arp, send_req, arp_req);
    init_req3(send_req, arp_req);
    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    loop_broadcast(arp);

    return (0);
}