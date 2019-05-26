/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** if.c
*/

#include "arpspoofing.h"

int ifr_getter(arp_t *arp)
{
    int sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));

    if (sd <= 0) {
        error("Socket failed");
        checkfd(sd);
    }

    if (strlen(arp->iface) > (IFNAMSIZ - 1)) {
        error("Too long interface name");
        checkfd(sd);
    }
    strcpy(arp->ifr.ifr_name, arp->iface);

    if (ioctl(sd, SIOCGIFINDEX, &arp->ifr) == -1) {
        error("SIOCGIFINDEX failed");
        checkfd(sd);
    }
    arp->ifindex = arp->ifr.ifr_ifindex;

    if (ioctl(sd, SIOCGIFHWADDR, &arp->ifr) == -1) {
        error("SIOCGIFINDEX failed again");
        checkfd(sd);
    }
    memcpy(arp->mac, arp->ifr.ifr_hwaddr.sa_data, MAC_LEN);

    if (ifr_ipv4_getter(arp, sd))
        checkfd(sd);

    return (0);
}