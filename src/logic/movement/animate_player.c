/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** animate_player.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

static void update_frame_boy(player_t *player, sfIntRect *frame)
{
    static sfClock *clock = NULL;
    sfTime elapsed_time;

    if (!clock) {
        clock = sfClock_create();
    }
    elapsed_time = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed_time) > ANIMATION_DURATION) {
        frame->left += 24;
        if (frame->left >= 24 * 4)
            frame->left = 0;
        sfClock_restart(clock);
    }
    sfSprite_setTextureRect(player->sprite->sprite, *frame);
}

static void animate_boy(player_t *player, unsigned short *keybinds)
{
    static sfIntRect frame = {0, 0, 24, 24};

    if (sfKeyboard_isKeyPressed(keybinds[BIND_UP])) {
        frame.top = 24 * 3;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_LEFT])) {
        frame.top = 24;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_DOWN])) {
        frame.top = 0;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_RIGHT])) {
        frame.top = 24 * 2;
    }
    update_frame_boy(player, &frame);
}

static void update_frame_girl(player_t *player, sfIntRect *frame)
{
    static sfClock *clock = NULL;
    sfTime elapsed_time;

    if (!clock) {
        clock = sfClock_create();
    }
    elapsed_time = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed_time) > ANIMATION_DURATION) {
        frame->left += 32;
        if (frame->left >= 32 * 6)
            frame->left = 0;
        sfClock_restart(clock);
    }
    sfSprite_setTextureRect(player->sprite->sprite, *frame);
}

static void animate_girl(player_t *player, unsigned short *keybinds)
{
    static sfIntRect frame = {0, 0, 32, 32};

    if (sfKeyboard_isKeyPressed(keybinds[BIND_DOWN])) {
        frame.top = 0;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_LEFT])) {
        frame.top = 32 * 2;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_UP])) {
        frame.top = 32;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_RIGHT])) {
        frame.top = 32 * 3;
    }
    update_frame_girl(player, &frame);
}

void animate_player(game_t *game)
{
    if (game->player->male) {
        animate_boy(game->player, game->keybinds);
    } else {
        animate_girl(game->player, game->keybinds);
    }
}
