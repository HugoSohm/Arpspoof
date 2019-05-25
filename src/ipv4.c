/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** ipv4.c
*/

#include "arpspoofing.h"

int int_ip4(struct sockaddr *addr, uint32_t *ip)
{
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *i = (struct sockaddr_in *) addr;
        *ip = i->sin_addr.s_addr;
        return (0);
    } else
        error("Not AF_INET");
}

int get_if_ip4(int fd, const char *ifname, uint32_t *ip)
{
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(struct ifreq));

    if (strlen(ifname) > (IFNAMSIZ - 1))
        error("Too long interface name");

    strcpy(ifr.ifr_name, ifname);

    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1)
        error("SIOCGIFADDR failed");

    int_ip4(&ifr.ifr_addr, ip);

    return (0);
}