/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** sprite.c
*/

#include <stdlib.h>
#include "my.h"

void center_sprite(sfSprite *sprite)
{
    sfFloatRect bounds = sfSprite_getLocalBounds(sprite);
    sfVector2f origin = {.x = bounds.width / 2.0, .y = bounds.height / 2.0};

    sfSprite_setOrigin(sprite, origin);
}

sprite_t *create_sprite(char const *file)
{
    sprite_t *new = malloc(sizeof(sprite_t));

    if (!new) {
        return NULL;
    }
    new->texture = sfTexture_createFromFile(file, NULL);
    if (new->texture != NULL) {
        new->sprite = sfSprite_create();
        if (new->sprite != NULL) {
            sfSprite_setTexture(new->sprite, new->texture, sfTrue);
        } else {
            sfTexture_destroy(new->texture);
            free(new);
            return NULL;
        }
    } else {
        free(new);
        return NULL;
    }
    return new;
}

void destroy_sprite(sprite_t *sprite)
{
    if (sprite != NULL) {
        if (sprite->sprite != NULL) {
            sfSprite_destroy(sprite->sprite);
        }
        if (sprite->texture != NULL) {
            sfTexture_destroy(sprite->texture);
        }
        free(sprite);
    }
}
