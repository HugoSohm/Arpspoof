/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** print_flags.c
*/

#include "arpspoofing.h"

int print_broadcast(char **av)
{
    arp_t *arp = init_arp(av);
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);

    ifr_getter2(arp);
    set_header3(arp, send_req, arp_req);
    init_request(send_req, arp_req);
    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    print_loop(arp);

    return (0);
}

int print_spoof(char **av)
{
    arp_t *arp = init_arp(av);
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);

    sscanf(av[5], "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx%*c",
        &arp->bytes[0], &arp->bytes[1], &arp->bytes[2],
        &arp->bytes[3], &arp->bytes[4], &arp->bytes[5]);

    ifr_getter2(arp);
    set_header2(arp, send_req, arp_req);
    init_reply(send_req, arp_req);

    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    print_loop(arp);

    return (0);
}

int print_loop(arp_t *arp)
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

int print_mac(arp_t *arp)
{
    printf("Found victim's MAC address: %02x:%02x:%02x:%02x:%02x:%02x\n",
        arp->target_mac[0],
        arp->target_mac[1],
        arp->target_mac[2],
        arp->target_mac[3],
        arp->target_mac[4],
        arp->target_mac[5]);
}