/*
** EPITECH PROJECT, 2018
** NWP_myarpspoofing_2018
** File description:
** arpspoofing.c
*/

#include "arpspoofing.h"

void checkfd(int fd)
{
    if (fd) {
        close(fd);
    }
}

int arpspoofing(char **av)
{
    arp_t *arp = init_arp(av);
    uint32_t dst = inet_addr(arp->dest);
    char mac[MAC_LEN];
    int ifindex;
    int arp_fd;
    int read;
    int src;

    if (dst == 0 || dst == 0xffffffff) {
        printf("Invalid source IP\n");
        return (84);
    }
    if (get_if_info(arp->iface, &src, mac, &ifindex)) {
        perror("get_if_info failed");
        checkfd(arp_fd);
    }
    if (bind_arp(ifindex, &arp_fd)) {
        perror("Failed to bind_arp()");
        checkfd(arp_fd);
    }
    if (send_arp(arp_fd, ifindex, mac, src, dst)) {
        perror("Failed to send_arp");
        checkfd(arp_fd);
    }

    while (1) {
        read = read_arp(arp_fd);
        if (read == 0) {
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
    if (ac != 3) {
        help();
        return (84);
    } else {
        return (arpspoofing(av));
    }
    return (0);
}