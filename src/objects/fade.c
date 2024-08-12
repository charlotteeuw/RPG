/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** fade.c
*/

#include <stdlib.h>
#include "my.h"

fade_t *create_fade(void)
{
    fade_t *fade = malloc(sizeof(fade_t));
    sfVector2f size = {1920, 1080};

    if (fade != NULL) {
        fade->img = sfRectangleShape_create();
        if (fade->img != NULL) {
            sfRectangleShape_setSize(fade->img, size);
            sfRectangleShape_setFillColor(fade->img, sfBlack);
        }
        fade->active = false;
    }
    return fade;
}

void update_fade(fade_t *fade)
{
    static sfColor color = {0, 0, 0, 255};

    if (fade != NULL && fade->active) {
        color.a -= 5;
        if (color.a > 0 && fade->img != NULL) {
            sfRectangleShape_setFillColor(fade->img, color);
        } else {
            fade->active = false;
            color.a = 255;
        }
    }
}

void activate_fade(fade_t *fade)
{
    if (fade != NULL && fade->img != NULL) {
        sfRectangleShape_setFillColor(fade->img, sfBlack);
        fade->active = true;
    }
}

void destroy_fade(fade_t *fade)
{
    if (fade != NULL) {
        if (fade->img != NULL) {
            sfRectangleShape_destroy(fade->img);
        }
        free(fade);
    }
}
