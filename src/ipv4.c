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
    } else {
        perror("Not AF_INET");
        return (1);
    }
}

int format_ip4(struct sockaddr *addr, char *out)
{
    if (addr->sa_family == AF_INET) {
        struct sockaddr_in *i = (struct sockaddr_in *) addr;
        const char *ip = inet_ntoa(i->sin_addr);
        if (!ip) {
            return (-2);
        } else {
            strcpy(out, ip);
            return (0);
        }
    } else {
        return (-1);
    }
}

int get_if_ip4(int fd, const char *ifname, uint32_t *ip)
{
    int err = -1;
    struct ifreq ifr;

    memset(&ifr, 0, sizeof(struct ifreq));

    if (strlen(ifname) > (IFNAMSIZ - 1)) {
        perror("Too long interface name");
        return (err);
    }
    strcpy(ifr.ifr_name, ifname);

    if (ioctl(fd, SIOCGIFADDR, &ifr) == -1) {
        perror("SIOCGIFADDR");
        return (err);
    }

    if (int_ip4(&ifr.ifr_addr, ip))
        return (err);
    err = 0;
}