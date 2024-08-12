/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** my_splitstr.c
*/

#include <stdlib.h>
#include "my.h"

static bool is_delimiter(char const c, const char *delim)
{
    for (size_t i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i]) {
            return true;
        }
    }
    return false;
}

static size_t new_size(char const *str, char const *delim)
{
    bool separator = false;
    bool in_word = false;
    size_t n = 0;

    for (size_t i = 0; str != NULL && delim != NULL && str[i] != '\0'; i++) {
        separator = is_delimiter(str[i], delim);
        if (separator && in_word) {
            in_word = false;
            n++;
        }
        if (!separator && !in_word) {
            in_word = true;
        }
    }
    if (in_word) {
        n++;
    }
    return n;
}

static char *new_element(char const *str, char const *delim, size_t *offset)
{
    char *new = NULL;
    size_t len = 0;

    while (str[*offset] != '\0' && is_delimiter(str[*offset], delim)) {
        (*offset)++;
    }
    while (str[*offset + len] != '\0' &&
        !is_delimiter(str[*offset + len], delim)) {
        len++;
    }
    new = malloc(sizeof(char) * (len + 1));
    if (new != NULL) {
        for (size_t j = 0; j < len; j++) {
            new[j] = str[*offset + j];
        }
        new[len] = '\0';
        (*offset) += len;
    }
    return new;
}

char **my_splitstr(char const *str, char const *delim)
{
    size_t len = new_size(str, delim);
    char **array = NULL;
    size_t offset = 0;

    if (len > 0) {
        array = malloc(sizeof(char *) * (len + 1));
    }
    if (!array) {
        return NULL;
    }
    for (size_t j = 0; j < len; j++) {
        array[j] = new_element(str, delim, &offset);
        if (!array[j]) {
            return NULL;
        }
    }
    array[len] = NULL;
    return array;
}
