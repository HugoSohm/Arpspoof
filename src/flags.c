/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** flags.c
*/

#include "arpspoofing.h"

int printBroadcast(char **av)
{
    arp_t *arp = init_arp(av);
    uint32_t dst = inet_addr(arp->dest);
    uint32_t src;
    int ifindex;
    char mac[MAC_LEN];
    int i = 0;
    unsigned char buffer[BUF_SIZE];
    struct ethhdr *send_req = (struct ethhdr *)buffer;
    arphdr_t *arp_req = (arphdr_t *)(buffer + ETH2_LEN);
    struct sockaddr_ll socket_address;

    ifr_getter(arp->iface, &src, mac, &ifindex);

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
    memset(arp_req->dest_mac, 0x00, MAC_LEN);
    memcpy(send_req->h_source, mac, MAC_LEN);
    memcpy(arp_req->src_mac, mac, MAC_LEN);
    memcpy(socket_address.sll_addr, mac, MAC_LEN);

    send_req->h_proto = htons(ETH_P_ARP);
    arp_req->hardware_type = htons(HW_TYPE);
    arp_req->protocol_type = htons(ETH_P_IP);
    arp_req->hardware_len = MAC_LEN;
    arp_req->protocol_len = IPV4_LEN;
    arp_req->opcode = htons(ARP_REQUEST);

    memcpy(arp_req->src_ip, &src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &dst, sizeof(uint32_t));

    while (i < 42) {
        if ((buffer[i] & 0xff) >= 0 && (buffer[i] & 0xff) <= 8)
            printf("0");
        printf("%x", buffer[i] & 0xff);
        if (i < 41)
            printf(" ");
        i++;
    }
    printf("\n");

    return (0);
}

int printSpoof(char **av)
{
    printf("Spoof flag is %s\n", av[4]);

    return (0);
}