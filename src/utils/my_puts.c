/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_puts.c
*/

#include <unistd.h>

size_t my_puts(int fd, char const *str)
{
    ssize_t bytes_written = 0;
    size_t len = 0;

    if (str != NULL) {
        while (str[len] != '\0') {
            len++;
        }
        bytes_written = write(fd, str, len);
    }
    return bytes_written;
}
