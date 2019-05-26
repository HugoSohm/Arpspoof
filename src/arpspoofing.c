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

    if (arp->dst == 0 || arp->dst == 0xffffffff)
        error("Invalid source IP");

    ifr_getter(arp);
    bind_arp(arp);
    send_arp(arp);

    while (42) {
        if (read_arp(arp) == 0)
            break;
    }
    while (42) {
        send_spoof(arp);
    }
    return (0);
}

int main(int ac, char **av)
{
    if (ac == 4)
        arpspoofing(av);
    else if (ac == 5 && strcmp(av[4], "--printBroadcast") == 0)
            print_broadcast(av);
    else if (ac == 6 && strcmp(av[4], "--printSpoof") == 0)
            print_spoof(av);
    else {
        help();
        return (84);
    }
    return (0);
}