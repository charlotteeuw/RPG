/*
** EPITECH PROJECT, 2024
** Library
** File description:
** my_freearray.c
*/

#include <stdlib.h>

void my_freearray(void *ptr)
{
    void **arr = ptr;

    for (size_t i = 0; arr[i]; i++) {
        free(arr[i]);
    }
    free(arr);
    return;
}
