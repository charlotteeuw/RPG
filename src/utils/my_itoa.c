/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_itoa.c
*/

#include <stdlib.h>
#include "my.h"

char *my_itoa(int nbr)
{
    int len = my_nbrlen(nbr);
    char *str = NULL;
    int temp = nbr;

    str = malloc(sizeof(char) * (len + 1));
    if (temp < 0) {
        temp = -temp;
    }
    if (str != NULL) {
        for (size_t i = len; i > 0; i--) {
            str[i - 1] = '0' + (temp % 10);
            temp /= 10;
        }
        str[len] = '\0';
    }
    if (nbr < 0) {
        str[0] = '-';
    }
    return str;
}
