/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arp.c
*/

#include "arpspoofing.h"

int read_arp(arp_t *arp, int fd)
{
    ssize_t length = recvfrom(fd, arp->buffer, BUF_SIZE, 0, NULL, NULL);
    arphdr_t *arp_resp = (arphdr_t *)(arp->buffer + ETH2_LEN);
    struct ethhdr *rcv_resp = (struct ethhdr *)arp->buffer;

    if (length == -1)
        error("Recvfrom failed");

    if (ntohs(rcv_resp->h_proto) != PROTO_ARP)
        error("Not an ARP packet");

    if (ntohs(arp_resp->opcode) != ARP_REPLY)
        error("Not an ARP reply");

    memset(&arp->sender_a, 0, sizeof(struct in_addr));
    memcpy(&arp->sender_a.s_addr, arp_resp->src_ip, sizeof(uint32_t));
    memcpy(arp->target_mac, arp_resp->src_mac, MAC_LEN);

    printf("Found victim's MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n",
        arp->target_mac[0],
        arp->target_mac[1],
        arp->target_mac[2],
        arp->target_mac[3],
        arp->target_mac[4],
        arp->target_mac[5]);

    return (0);
}

int bind_arp(arp_t *arp, int *fd)
{
    *fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    if (*fd < 1)
        error("Socket failed");

    memset(&arp->sll, 0, sizeof(struct sockaddr_ll));
    arp->sll.sll_family = AF_PACKET;
    arp->sll.sll_ifindex = arp->ifindex;

    if (bind(*fd, (struct sockaddr *)&arp->sll,
        sizeof(struct sockaddr_ll)) < 0) {
        error("Bind failed");
        if (*fd > 0)
            close(*fd);
    }
    return (0);
}

int send_arp(arp_t *arp, int fd)
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
    memset(send_req->h_dest, 0xff, MAC_LEN);
    memset(arp_req->dest_mac, 0x00, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);

    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REQUEST);

    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    arp->ret = sendto(fd, arp->buffer, 42, 0,
        (struct sockaddr *)&arp->socket_address, sizeof(arp->socket_address));
    if (arp->ret == -1)
        error("Sendto failed");

    return (0);
}