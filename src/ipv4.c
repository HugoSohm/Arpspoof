/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** ipv4.c
*/

#include "arpspoofing.h"

int init_ipv4(arp_t *arp, struct sockaddr *addr)
{
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *i = (struct sockaddr_in *) addr;
        arp->src = i->sin_addr.s_addr;
    } else
        error("Not AF_INET");

    return (0);
}

int ifr_ipv4_getter(arp_t *arp, int fd)
{
    memset(&arp->ifr, 0, sizeof(struct ifreq));

    if (strlen(arp->iface) > (IFNAMSIZ - 1))
        error("Too long interface name");

    strcpy(arp->ifr.ifr_name, arp->iface);

    if (ioctl(fd, SIOCGIFADDR, &arp->ifr) == -1)
        error("SIOCGIFADDR failed");

    init_ipv4(arp, &arp->ifr.ifr_addr);

    return (0);
}