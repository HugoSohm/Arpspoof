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

    printf("get_if_info for %s", ifname);

    if (sd <= 0) {
        perror("socket()");
        checkfd(sd);
    }

    if (strlen(ifname) > (IFNAMSIZ - 1)) {
        printf("Too long interface name, MAX = %i\n", IFNAMSIZ - 1);
        checkfd(sd);
    }
    strcpy(ifr.ifr_name, ifname);

    if (ioctl(sd, SIOCGIFINDEX, &ifr) == -1) {
        perror("SIOCGIFINDEX");
        checkfd(sd);
    }
    *ifindex = ifr.ifr_ifindex;
    printf("interface index is %d\n", *ifindex);

    if (ioctl(sd, SIOCGIFHWADDR, &ifr) == -1) {
        perror("SIOCGIFINDEX");
        checkfd(sd);
    }
    memcpy(mac, ifr.ifr_hwaddr.sa_data, MAC_LEN);

    if (get_if_ip4(sd, ifname, ip)) {
        checkfd(sd);
    }
    printf("get_if_info OK");
    return (0);
}