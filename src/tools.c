/*
** EPITECH PROJECT, 2018
** NWP_myarpspoof_2018
** File description:
** error.c
*/

#include "arpspoofing.h"

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