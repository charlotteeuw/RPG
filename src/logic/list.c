/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** list.c
*/

#include <stdlib.h>
#include "my.h"

void append_to_list(list_t **head, void *data)
{
    list_t *new = NULL;

    if (data != NULL) {
        new = malloc(sizeof(list_t));
        if (new != NULL) {
            new->data = data;
            new->next = (*head);
            (*head) = new;
        }
    }
}

void destroy_list(list_t *list, void (*destroy)(void *))
{
    list_t *next = NULL;

    for (list_t *temp = list; temp != NULL; temp = next) {
        next = temp->next;
        if (temp->data != NULL) {
            destroy(temp->data);
        }
        free(temp);
    }
}
