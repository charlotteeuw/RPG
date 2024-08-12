/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** game.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

static void destroy_outside_drawer(outside_t *outside)
{
    if (outside->sunset_bg != NULL) {
        destroy_sprite(outside->sunset_bg);
    }
    if (outside->collision != NULL) {
        sfImage_destroy(outside->collision);
    }
}

void destroy_outside(outside_t *outside)
{
    if (outside != NULL) {
        if (outside->bg != NULL) {
            destroy_sprite(outside->bg);
        }
        if (outside->up_bg != NULL) {
            destroy_sprite(outside->up_bg);
        }
        if (outside->night_bg != NULL) {
            destroy_sprite(outside->night_bg);
        }
        if (outside->dialogue != NULL) {
            destroy_sprite(outside->dialogue);
        }
        if (outside->icon != NULL) {
            destroy_sprite(outside->icon);
        }
        destroy_outside_drawer(outside);
        free(outside);
    }
}

static void scale_sprites(outside_t *outside)
{
    sfSprite_setScale(outside->bg->sprite, (sfVector2f){5, 5});
    sfSprite_setScale(outside->up_bg->sprite, (sfVector2f){5, 5});
    sfSprite_setScale(outside->night_bg->sprite, (sfVector2f){5, 5});
    sfSprite_setScale(outside->sunset_bg->sprite, (sfVector2f){5, 5});
    sfSprite_setScale(outside->dialogue->sprite, (sfVector2f){3, 3});
    sfSprite_setScale(outside->icon->sprite, (sfVector2f){0.7, 0.7});
}

outside_t *create_outside(void)
{
    outside_t *outside = malloc(sizeof(outside_t));

    if (outside != NULL) {
        outside->passed = 0;
        outside->passed_final = 0;
        outside->passed_end = 0;
        outside->passed_night = 0;
        outside->night = 0;
        outside->bg = create_sprite("./assets/images/map.png");
        outside->up_bg = create_sprite("./assets/images/map_up.png");
        outside->night_bg = create_sprite("./assets/images/map_night.png");
        outside->sunset_bg = create_sprite("./assets/images/map_sunset.png");
        outside->dialogue = create_sprite("./assets/images/dialogue.png");
        outside->icon = create_sprite("./assets/images/animal_icon.png");
        outside->collision = sfImage_createFromFile(
            "./assets/images/map_collision_scale.png");
        scale_sprites(outside);
    }
    return outside;
}

void start_game(game_t *game, sfVector2f pos)
{
    game->scene = SCENE_OUTSIDE;
    game->outside->is_dialogue = 1;
    game->outside->text = create_dialogue_text("./assets/dialogue/quest1.txt",
        game->player->name);
    sfSprite_setPosition(game->player->sprite->sprite, pos);
    game->player->pos = pos;
    setposition_view(game->window, pos);
}
