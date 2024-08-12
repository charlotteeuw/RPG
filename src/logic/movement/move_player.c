/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** move_player.c
*/

#include "my_def.h"
#include "my.h"
#include <stdio.h>

static void diagonal_move(sfVector2f *move)
{
    if (move->x != 0 && move->y != 0) {
        move->x = move->x / 2;
        move->y = move->y / 2;
    }
    return;
}

static sfVector2f retrieve_move(float delta, unsigned short *keybinds,
    game_t *game)
{
    sfVector2f move = {0, 0};
    float speed = game->player->quests->fast;

    if (sfKeyboard_isKeyPressed(keybinds[BIND_SPRINT])) {
        speed = 500;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_DOWN])) {
        move.y = delta * speed;
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_LEFT])) {
        move.x = -(delta * speed);
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_UP])) {
        move.y = -(delta * speed);
    }
    if (sfKeyboard_isKeyPressed(keybinds[BIND_RIGHT])) {
        move.x = delta * speed;
    }
    diagonal_move(&move);
    return move;
}

sfVector2f move_player(game_t *game)
{
    float delta = restart_clock(game->player->clock);
    sfVector2f move = retrieve_move(delta, game->keybinds, game);

    if (move.x != 0 || move.y != 0) {
        animate_player(game);
    }
    analyse_collision(game, &move);
    if (move.x != 0 || move.y != 0) {
        update_cat_position(game, move);
        sfSprite_move(game->player->sprite->sprite, move);
        game->player->pos = sfSprite_getPosition(game->player->sprite->sprite);
    }
    return move;
}
