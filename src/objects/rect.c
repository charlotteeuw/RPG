/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** rect.c
*/

#include "my_def.h"
#include "my.h"

void center_rect(sfRectangleShape *rect, bool x, bool y)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(rect);
    sfVector2f origin = {0};

    if (x) {
        origin.x = bounds.width / 2.0;
    } else {
        origin.x = 0;
    }
    if (y) {
        origin.y = bounds.height / 2.0;
    } else {
        origin.y = 0;
    }
    sfRectangleShape_setOrigin(rect, origin);
}

sfRectangleShape *create_rect(sfVector2f position,
    sfVector2f size, sfColor color)
{
    sfRectangleShape *rect = sfRectangleShape_create();

    if (rect != NULL) {
        sfRectangleShape_setSize(rect, size);
        sfRectangleShape_setFillColor(rect, color);
        sfRectangleShape_setPosition(rect, position);
    }
    return rect;
}
