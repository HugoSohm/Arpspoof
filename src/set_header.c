/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** set_header.c
*/

#include "arpspoofing.h"

int set_header(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req)
{
    memset(arp->buffer, 0, sizeof(arp->buffer));
    memset(send_req->h_dest, 0xff, MAC_LEN);
    memset(arp_req->dest_mac, 0x00, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);
}

int set_header1(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req)
{
    memset(arp->buffer, 0, sizeof(arp->buffer));
    memcpy(send_req->h_dest, arp->target_mac, MAC_LEN);
    memcpy(arp_req->dest_mac, arp->target_mac, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);
}

int set_header2(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req)
{
    memset(arp->buffer, 0, sizeof(arp->buffer));
    memcpy(send_req->h_dest, arp->bytes, MAC_LEN);
    memcpy(arp_req->dest_mac, arp->bytes, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);
}

int set_header3(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req)
{
    memset(arp->buffer, 0, sizeof(arp->buffer));
    memset(send_req->h_dest, 0xff, MAC_LEN);
    memset(arp_req->dest_mac, 0xff, MAC_LEN);
    memcpy(send_req->h_source, arp->mac, MAC_LEN);
    memcpy(arp_req->src_mac, arp->mac, MAC_LEN);
    memcpy(arp->socket_address.sll_addr, arp->mac, MAC_LEN);
}