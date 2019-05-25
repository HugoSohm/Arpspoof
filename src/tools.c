/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** error.c
*/

#include "arpspoofing.h"

void help(void)
{
    printf("USAGE:\n\n");
    printf("\tsrc_ip\tis the source IP.\n");
    printf("\tdest_ip\tis the destination IP.\n");
    printf("\tiface\tis the interface to use to send/receive packets.\n");
}

int error(char *str)
{
    perror(str);
    exit(84);
}

void checkfd(int fd)
{
    if (fd)
        close(fd);
}