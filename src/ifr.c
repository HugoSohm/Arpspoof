/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** if.c
*/

#include "arpspoofing.h"

int ifr_getter2(arp_t *arp)
{
    arp->fd = socket(AF_INET, SOCK_DGRAM, 0);

    if (arp->fd <= 0)
        error("Socket failed");

    if (strlen(arp->iface) > (IFNAMSIZ - 1))
        error("Too long interface name");
    strcpy(arp->ifr.ifr_name, arp->iface);

    if (ioctl(arp->fd, SIOCGIFINDEX, &arp->ifr) == -1)
        error("SIOCGIFINDEX failed");
    arp->ifindex = arp->ifr.ifr_ifindex;

    if (ioctl(arp->fd, SIOCGIFHWADDR, &arp->ifr) == -1)
        error("SIOCGIFINDEX failed again");
    memcpy(arp->mac, arp->ifr.ifr_hwaddr.sa_data, MAC_LEN);

    return (0);
}

int ifr_getter(arp_t *arp)
{
    arp->fd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    if (arp->fd <= 0)
        error("Socket failed");

    if (strlen(arp->iface) > (IFNAMSIZ - 1))
        error("Too long interface name");
    strcpy(arp->ifr.ifr_name, arp->iface);

    if (ioctl(arp->fd, SIOCGIFINDEX, &arp->ifr) == -1)
        error("SIOCGIFINDEX failed");
    arp->ifindex = arp->ifr.ifr_ifindex;

    if (ioctl(arp->fd, SIOCGIFHWADDR, &arp->ifr) == -1)
        error("SIOCGIFINDEX failed again");
    memcpy(arp->mac, arp->ifr.ifr_hwaddr.sa_data, MAC_LEN);

    if (ifr_ipv4_getter(arp))
        checkfd(arp->fd);
    return (0);
}