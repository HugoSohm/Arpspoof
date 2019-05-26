/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** init.c
*/

#include "arpspoofing.h"

arp_t *init_arp(char **av)
{
    arp_t *arp = malloc(sizeof(*arp));

    arp->sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    arp->dest = av[2];
    arp->dst = inet_addr(av[2]);
    arp->iface = av[3];

    return (arp);
}