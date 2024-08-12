/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_strlen.c
*/

#include <stddef.h>

size_t my_strlen(char const *str)
{
    size_t len = 0;

    if (str != NULL) {
        while (str[len] != '\0') {
            len++;
        }
    }
    return len;
}
