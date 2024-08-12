/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** progress.c
*/

#include "my_def.h"
#include <stdlib.h>
#include "my.h"

static sfRectangleShape *create_bar(sfVector2f position,
    sfVector2f size, sfColor color)
{
    sfRectangleShape *bar = sfRectangleShape_create();

    if (bar != NULL) {
        sfRectangleShape_setPosition(bar, position);
        sfRectangleShape_setFillColor(bar, color);
        sfRectangleShape_setSize(bar, size);
    }
    return bar;
}

progress_t *create_progress(sfVector2f position, sfVector2f size)
{
    progress_t *bar = malloc(sizeof(progress_t));
    sfVector2f foreground_size = {0.0, size.y};

    if (bar != NULL) {
        bar->foreground = create_bar(position, foreground_size, C_LIGHT_TEXT);
        bar->background = create_bar(position, size, sfWhite);
        if (bar->background != NULL) {
            sfRectangleShape_setOutlineColor(bar->background, C_DARK_TEXT);
            sfRectangleShape_setOutlineThickness(bar->background, 2);
        }
    }
    return bar;
}

void destroy_progress(progress_t *bar)
{
    if (bar != NULL) {
        if (bar->background != NULL) {
            sfRectangleShape_destroy(bar->background);
        }
        if (bar->foreground != NULL) {
            sfRectangleShape_destroy(bar->foreground);
        }
        free(bar);
    }
}
