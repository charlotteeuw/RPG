/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** distances.c
*/

#include <math.h>
#include "my.h"

float distance_between_coords(sfVector2f from, sfVector2f to)
{
    float dx = to.x - from.x;
    float dy = to.y - from.y;

    return sqrt(dx * dx + dy * dy);
}
