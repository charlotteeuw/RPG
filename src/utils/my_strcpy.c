/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_strcpy.c
*/

#include <stddef.h>

char *my_strcpy(char *restrict dst, char const *restrict src)
{
    size_t i = 0;

    if (dst != NULL && src != NULL) {
        while (src[i] != '\0') {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
        return dst;
    }
    return NULL;
}
