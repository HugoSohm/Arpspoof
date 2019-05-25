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
#define ARP_REQUEST 0x01
#define ARP_REPLY   0x02
#define IPV4_LEN    4
#define ETH2_LEN    14
#define BUF_SIZE    60
#define HW_TYPE     1
#define MAC_LEN     6

typedef struct arp_s {
    const char *iface;
    const char *src;
    const char *dest;
    unsigned char target_mac[6];
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

// Arpspoofing
int arpspoofing(char **av);
int main(int ac, char **av);
void help(void);

// Functions
void checkfd(int fd);
int error(char *str);

// Get infos
int ifr_getter(const char *ifname, uint32_t *ip, char *mac, int *ifindex);

// Spoof
int send_spoof(arp_t *arp, int fd, int ifindex, char *src_mac,
    uint32_t src_ip, uint32_t dst_ip);

// Arp package
int send_arp(int fd, int ifindex, char *src_mac,
    uint32_t src_ip, uint32_t dst_ip);
int bind_arp(int ifindex, int *fd);
int read_arp(int fd, arp_t *arp);

// Initalisation
arp_t *init_arp(char **av);

// Ipv4
int init_ipv4(struct sockaddr *addr, uint32_t *ip);
int ifr_ipv4_getter(int fd, const char *ifname, uint32_t *ip);

#endif