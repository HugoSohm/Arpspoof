/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arp.c
*/

#include "arpspoofing.h"

int read_arp(arp_t *arp)
{
    ssize_t length = recvfrom(arp->fd, arp->buffer, BUF_SIZE, 0, NULL, NULL);
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

    print_mac(arp);

    return (0);
}

int bind_arp(arp_t *arp)
{
    if (arp->fd < 1)
        error("Socket failed");

    memset(&arp->sll, 0, sizeof(struct sockaddr_ll));
    arp->sll.sll_family = AF_PACKET;
    arp->sll.sll_ifindex = arp->ifindex;

    if (bind(arp->fd, (struct sockaddr *)&arp->sll,
        sizeof(struct sockaddr_ll)) < 0) {
        error("Bind failed");
        if (arp->fd > 0)
            close(arp->fd);
    }
    return (0);
}

int send_arp(arp_t *arp)
{
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);

    init_arph(arp);
    set_header(arp, send_req, arp_req);
    init_request(send_req, arp_req);

    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    arp->ret = sendto(arp->fd, arp->buffer, 42, 0,
        (struct sockaddr *)&arp->socket_address, sizeof(arp->socket_address));
    if (arp->ret == -1)
        error("Sendto failed");

    return (0);
}