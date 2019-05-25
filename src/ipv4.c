/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** ipv4.c
*/

#include "arpspoofing.h"

int init_ipv4(struct sockaddr *addr, uint32_t *ip)
{
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *i = (struct sockaddr_in *) addr;
        *ip = i->sin_addr.s_addr;
    } else
        error("Not AF_INET");
    
    return (0);
}

int ifr_ipv4_getter(int fd, const char *ifname, uint32_t *ip)
{
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(struct ifreq));

    if (strlen(ifname) > (IFNAMSIZ - 1))
        error("Too long interface name");

    strcpy(ifr.ifr_name, ifname);

    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1)
        error("SIOCGIFADDR failed");

    init_ipv4(&ifr.ifr_addr, ip);

    return (0);
}