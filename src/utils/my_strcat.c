/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_strcat.c
*/

#include <stddef.h>

char *my_strcat(char *restrict dst, char const *restrict src)
{
    size_t len = 0;
    size_t i = 0;

    if (dst != NULL && src != NULL) {
        while (dst[len] != '\0') {
            len++;
        }
        while (src[i] != '\0') {
            dst[len + i] = src[i];
            i++;
        }
        dst[len + i] = '\0';
        return dst;
    } else {
        return NULL;
    }
}
