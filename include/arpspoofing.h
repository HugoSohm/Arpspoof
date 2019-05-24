/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arpspoofing.h
*/

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <asm/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
#include <linux/if_arp.h>
#include <arpa/inet.h>

#ifndef ARPSPOOFING_H
#define ARPSPOOFING_H

#define ETH_TYPE    0x0800
#define PROTO_ARP   0x0806
#define ETH2_HEADER_LEN 14
#define HW_TYPE     1
#define MAC_LEN     6
#define IPV4_LEN    4
#define ARP_REQUEST 0x01
#define ARP_REPLY   0x02
#define BUF_SIZE    60

typedef struct arp_s {
    const char *iface;
    const char *src;
    const char *dest;
    int sock;
} arp_t;

typedef struct arphdr_s {
    uint16_t    hardware_type;
    uint16_t    protocol_type;
    char        hardware_len;
    char        protocol_len;
    uint16_t    opcode;
    char        src_mac[MAC_LEN];
    char        src_ip[IPV4_LEN];
    char        dest_mac[MAC_LEN];
    char        dest_ip[IPV4_LEN];
} arphdr_t;

// Main arpspoofing
int arpspoofing(char **av);
int main(int ac, char **av);
void help(void);

// Check
void checkfd(int fd);
void checkfd2(int *fd);

// If info
int get_if_info(const char *ifname, uint32_t *ip, char *mac, int *ifindex);

// Arp package
int send_arp(int fd, int ifindex, const unsigned char *src_mac,
    uint32_t src_ip, uint32_t dst_ip);
int bind_arp(int ifindex, int *fd);
int read_arp(int fd);

// Initalisation
arp_t *init_arp(char **av);

// IPV4
int int_ip4(struct sockaddr *addr, uint32_t *ip);
int format_ip4(struct sockaddr *addr, char *out);
int get_if_ip4(int fd, const char *ifname, uint32_t *ip);

#endif