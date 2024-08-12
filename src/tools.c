/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** tools.c
*/

#include "my_def.h"
#include <stdlib.h>
#include <time.h>
#include "my.h"

char *create_date(void)
{
    char *str = malloc(sizeof(char) * DATE_LEN);
    time_t rawtime = {0};
    struct tm *timeinfo;

    if (time(&rawtime) != -1) {
        timeinfo = localtime(&rawtime);
        if (timeinfo != NULL) {
            strftime(str, DATE_LEN, "%Y_%m_%d_%H_%M_%S", timeinfo);
        }
    }
    return str;
}

float restart_clock(sfClock *clock)
{
    sfTime elapsed = sfTime_Zero;
    float seconds = 0;

    if (clock != NULL) {
        elapsed = sfClock_restart(clock);
        seconds = sfTime_asSeconds(elapsed);
    }
    return seconds;
}

sfBool is_in_sprite(sfSprite const *sprite, float x, float y)
{
    sfFloatRect bounds = {0};
    sfBool in = sfFalse;

    if (sprite != NULL) {
        bounds = sfSprite_getGlobalBounds(sprite);
        in = sfFloatRect_contains(&bounds, x, y);
    }
    return in;
}

sfBool is_in_rect(sfRectangleShape const *rectangle, float x, float y)
{
    sfFloatRect bounds = {0};
    sfBool in = sfFalse;

    if (rectangle != NULL) {
        bounds = sfRectangleShape_getGlobalBounds(rectangle);
        in = sfFloatRect_contains(&bounds, x, y);
    }
    return in;
}

sfBool is_in_circle(sfCircleShape const *circle, float x, float y)
{
    sfFloatRect bounds = {0};
    sfBool in = sfFalse;

    if (circle != NULL) {
        bounds = sfCircleShape_getGlobalBounds(circle);
        in = sfFloatRect_contains(&bounds, x, y);
    }
    return in;
}
