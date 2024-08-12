/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** cat_movement.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

static void move_cat(game_t *game, sfIntRect *frame, sfVector2f move)
{
    static sfClock *clock;
    sfTime elapsed_time;

    if (!clock) {
        clock = sfClock_create();
    }
    elapsed_time = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed_time) > ANIMATION_DURATION) {
        frame->left += 32;
        if (frame->left >= 32 * 3)
            frame->left = 0;
        sfClock_restart(clock);
    }
    sfSprite_setTextureRect(game->cat->sprite, *frame);
    sfSprite_move(game->cat->sprite, move);
}

void update_cat_position(game_t *game, sfVector2f move)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player->sprite->sprite);
    sfVector2f pos = {player_pos.x - 30, player_pos.y};
    static sfIntRect frame = {0, 0, 32, 32};

    if (move.x > 0) {
        frame.top = 32 * 2;
    }
    if (move.x < 0) {
        frame.top = 32;
    }
    if (move.y < 0) {
        frame.top = 32 * 3;
    }
    if (move.y > 0) {
        frame.top = 0;
    }
    sfSprite_setPosition(game->cat->sprite, pos);
    move_cat(game, &frame, move);
}
