/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arp.c
*/

#include "arpspoofing.h"

int read_arp(int fd, arp_t *arp)
{
    unsigned char buffer[BUF_SIZE];
    ssize_t length = recvfrom(fd, buffer, BUF_SIZE, 0, NULL, NULL);
    arphdr_t *arp_resp = (arphdr_t *)(buffer + ETH2_LEN);
    struct ethhdr *rcv_resp = (struct ethhdr *)buffer;
    struct in_addr sender_a;

    if (length == -1)
        error("Recvfrom failed");

    if (ntohs(rcv_resp->h_proto) != PROTO_ARP)
        error("Not an ARP packet");

    if (ntohs(arp_resp->opcode) != ARP_REPLY)
        error("Not an ARP reply");

    memset(&sender_a, 0, sizeof(struct in_addr));
    memcpy(&sender_a.s_addr, arp_resp->src_ip, sizeof(uint32_t));
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

int bind_arp(int ifindex, int *fd)
{
    struct sockaddr_ll sll;
    *fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    if (*fd < 1)
        error("Socket failed");

    memset(&sll, 0, sizeof(struct sockaddr_ll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifindex;

    if (bind(*fd, (struct sockaddr *)&sll, sizeof(struct sockaddr_ll)) < 0) {
        error("Bind failed");
        if (*fd > 0)
            close(*fd);
    }
    return (0);
}

int send_arp(int fd, int ifindex, char *src_mac,
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
    memset(send_req->h_dest, 0xff, MAC_LEN);
    memset(arp_req->dest_mac, 0xff, MAC_LEN);
    memcpy(send_req->h_source, src_mac, MAC_LEN);
    memcpy(arp_req->src_mac, src_mac, MAC_LEN);
    memcpy(socket_address.sll_addr, src_mac, MAC_LEN);

    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REQUEST);

    memcpy(arp_req->src_ip, &src_ip, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &dst_ip, sizeof(uint32_t));

    ret = sendto(fd, buffer, 42, 0, (struct sockaddr *) &socket_address, sizeof(socket_address));
    if (ret == -1)
        error("Sendto failed");

    return (0);
}