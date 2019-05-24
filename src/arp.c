/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arp.c
*/

#include "arpspoofing.h"

int send_arp(int fd, int ifindex, const unsigned char *src_mac,
    uint32_t src_ip, uint32_t dst_ip)
{
    unsigned char buffer[BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));

    struct sockaddr_ll socket_address;
    socket_address.sll_family = AF_PACKET;
    socket_address.sll_protocol = htons(ETH_P_ARP);
    socket_address.sll_ifindex = ifindex;
    socket_address.sll_hatype = htons(ARPHRD_ETHER);
    socket_address.sll_pkttype = (PACKET_BROADCAST);
    socket_address.sll_halen = MAC_LEN;
    socket_address.sll_addr[6] = 0x00;
    socket_address.sll_addr[7] = 0x00;

    struct ethhdr *send_req = (struct ethhdr *) buffer;
    arphdr_t *arph = (arphdr_t *)(buffer + ETH2_HEADER_LEN);
    ssize_t ret = 0;

    memset(send_req->h_dest, 0xff, MAC_LEN);
    memset(arph->dest_mac, 0x00, MAC_LEN);
    memcpy(send_req->h_source, src_mac, MAC_LEN);
    memcpy(arph->src_mac, src_mac, MAC_LEN);
    memcpy(socket_address.sll_addr, src_mac, MAC_LEN);

    send_req->h_proto = htons(ETH_P_ARP);
    arph->hardware_type = htons(HW_TYPE);
    arph->protocol_type = htons(ETH_P_IP);
    arph->hardware_len = MAC_LEN;
    arph->protocol_len = IPV4_LEN;
    arph->opcode = htons(ARP_REQUEST);
    memcpy(arph->src_ip, &src_ip, sizeof(uint32_t));
    memcpy(arph->dest_ip, &dst_ip, sizeof(uint32_t));

    ret = sendto(fd, buffer, 42, 0, (struct sockaddr *)&socket_address,
        sizeof(socket_address));
    if (ret == -1) {
        perror("sendto():");
    }
}

int bind_arp(int ifindex, int *fd)
{
    *fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    if (*fd < 1)
        perror("socket()");

    printf("Binding to ifindex %i", ifindex);
    struct sockaddr_ll sll;
    memset(&sll, 0, sizeof(struct sockaddr_ll));
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifindex;

    if (bind(*fd, (struct sockaddr *)&sll, sizeof(struct sockaddr_ll)) < 0) {
        perror("bind");
        if (*fd > 0)
            close(*fd);
    }
    return (0);
}

int read_arp(int fd)
{
    unsigned char buffer[BUF_SIZE];
    ssize_t length = recvfrom(fd, buffer, BUF_SIZE, 0, NULL, NULL);

    if (length == -1)
        perror("recvfrom()");

    struct ethhdr *rcv_resp = (struct ethhdr *) buffer;
    arphdr_t *arp_resp = (arphdr_t *)(buffer + ETH2_HEADER_LEN);

    if (ntohs(rcv_resp->h_proto) != PROTO_ARP)
        perror("Not an ARP packet");

    if (ntohs(arp_resp->opcode) != ARP_REPLY)
        perror("Not an ARP reply");

    printf("received ARP len = %ld", length);
    struct in_addr sender_a;
    memset(&sender_a, 0, sizeof(struct in_addr));
    memcpy(&sender_a.s_addr, arp_resp->src_ip, sizeof(uint32_t));
    printf("Sender IP: %s", inet_ntoa(sender_a));

    printf("Sender MAC: %02X:%02X:%02X:%02X:%02X:%02X",
        arp_resp->src_mac[0],
        arp_resp->src_mac[1],
        arp_resp->src_mac[2],
        arp_resp->src_mac[3],
        arp_resp->src_mac[4],
        arp_resp->src_mac[5]);
}