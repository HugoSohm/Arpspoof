/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** if.c
*/

#include "arpspoofing.h"

int get_if_info(const char *ifname, uint32_t *ip, char *mac, int *ifindex)
{
    int sd = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ARP));
    struct ifreq ifr;

    if (sd <= 0) {
        error("Socket failed");
        checkfd(sd);
    }

    if (strlen(ifname) > (IFNAMSIZ - 1)) {
        error("Too long interface name");
        checkfd(sd);
    }
    strcpy(ifr.ifr_name, ifname);

    if (ioctl(sd, SIOCGIFINDEX, &ifr) == -1) {
        error("SIOCGIFINDEX failed");
        checkfd(sd);
    }
    *ifindex = ifr.ifr_ifindex;

    if (ioctl(sd, SIOCGIFHWADDR, &ifr) == -1) {
        error("SIOCGIFINDEX failed again");
        checkfd(sd);
    }
    memcpy(mac, ifr.ifr_hwaddr.sa_data, MAC_LEN);

    if (get_if_ip4(sd, ifname, ip))
        checkfd(sd);

    return (0);
}