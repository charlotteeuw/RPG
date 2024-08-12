/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_strdup.c
*/

#include <stdlib.h>

char *my_strdup(char const *str)
{
    char *copy = NULL;
    size_t len = 0;

    if (!str) {
        return NULL;
    }
    while (str[len] != '\0') {
        len++;
    }
    copy = malloc(sizeof(char) * (len + 1));
    if (copy != NULL) {
        for (size_t i = 0; i < len; i++) {
            copy[i] = str[i];
        }
        copy[len] = '\0';
    }
    return copy;
}
