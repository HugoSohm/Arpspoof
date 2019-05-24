/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arpspoofing.c
*/

#include "arpspoofing.h"

void checkfd(int fd)
{
    if (fd)
        close(fd);
}

int arpspoofing(char **av)
{
    arp_t *arp = init_arp(av);
    uint32_t dst = inet_addr(arp->dest);
    char mac[MAC_LEN];
    int ifindex;
    int fd;
    int read;
    int src;

    if (dst == 0 || dst == 0xffffffff) {
        printf("Invalid source IP\n");
        return (84);
    }

    get_if_info(arp->iface, &src, mac, &ifindex);
    bind_arp(ifindex, &fd);
    send_arp(fd, ifindex, mac, src, dst);

    while (42) {
        if (read_arp(fd) == 0) {
            printf("Got reply, break out");
            break;
        }
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
    if (ac != 4) {
        help();
        return (84);
    } else {
        return (arpspoofing(av));
    }
    return (0);
}