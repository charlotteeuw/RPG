/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_open.c
*/

#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

char *my_open(char const *filepath)
{
    int fd = open(filepath, O_RDONLY);
    char *content = NULL;
    struct stat sb = {0};

    if (fd < 0) {
        return content;
    }
    if (stat(filepath, &sb) != -1) {
        content = malloc(sizeof(char) * (sb.st_size + 1));
        if (content != NULL && read(fd, content, sb.st_size) != -1) {
            content[sb.st_size] = '\0';
        }
    }
    close(fd);
    return content;
}
