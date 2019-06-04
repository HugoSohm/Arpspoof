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
    struct sockaddr_ll socket_address;
    struct in_addr sender_a;
    struct sockaddr_ll sll;
    struct ifreq ifr;
    unsigned char buffer[BUF_SIZE];
    unsigned char target_mac[6];
    char mac[MAC_LEN];
    const char *iface;
    const char *dest;
    uint32_t src;
    uint32_t dst;
    ssize_t ret;
    int ifindex;
    int sock;
    int fd;
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
int main(int ac, char **av);
int arpspoofing(char **av);

// Functions
void checkfd(int fd);
int error(char *str);
void help(void);

// Get infos
int ifr_getter(arp_t *arp);
int ifr_getter2(arp_t *arp);

// Sending
int set_header(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req);
int init_req(struct ethhdr *send_req, arphdr_t *arp_req);
int init_arph(arp_t *arp);
int send_spoof(arp_t *arp);

// Print spoof
int init_arph2(arp_t *arp);
int set_header2(arp_t *arp, struct ethhdr *send_req,
    arphdr_t *arp_req, char **av);
int init_req2(struct ethhdr *send_req, arphdr_t *arp_req);
int print_spoof(char **av);

// Print broadcast
int init_arph3(arp_t *arp);
int set_header3(arp_t *arp, struct ethhdr *send_req, arphdr_t *arp_req);
int init_req3(struct ethhdr *send_req, arphdr_t *arp_req);
int print_broadcast(char **av);

// Arp package
int send_arp(arp_t *arp);
int bind_arp(arp_t *arp);
int read_arp(arp_t *arp);

// Initalisation
arp_t *init_arp(char **av);
int init_arph(arp_t *arp);
int init_req(struct ethhdr *send_req, arphdr_t *arp_req);

// Ipv4
int ifr_ipv4_getter(arp_t *arp);
int init_ipv4(arp_t *arp, struct sockaddr *addr);

#endif