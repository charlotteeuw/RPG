/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** movement.c
*/

#include "my.h"

const scene_t scene_movement[7] = {
    SCENE_OUTSIDE, SCENE_ROOM, SCENE_SHOP, SCENE_SPAWN, SCENE_TUTO,
    SCENE_SHERIFF, SCENE_BOSS
};

void setposition_view(sfRenderWindow *window, sfVector2f pos)
{
    sfView *view = sfView_copy(sfRenderWindow_getView(window));

    sfView_setCenter(view, pos);
    sfRenderWindow_setView(window, view);
    sfView_destroy(view);
}

void switch_player_movement(player_t *player, enum e_move move)
{
    switch (move) {
        case MOVING_ON:
            player->moving = true;
            break;
        case MOVING_OFF:
            player->moving = false;
            break;
        case SWITCH_MOVING:
            player->moving = !player->moving;
            break;
        default:
            break;
    }
    if (player->moving && player->clock != NULL) {
        sfClock_restart(player->clock);
    }
}

static bool can_entities_move(scene_t scene)
{
    for (scene_t i = 0; i < 7; i++) {
        if (scene != scene_movement[i]) {
            continue;
        }
        return true;
    }
    return false;
}

static void move_view(sfRenderWindow *window, sfVector2f move)
{
    sfView *view = sfView_copy(sfRenderWindow_getView(window));

    if (view != NULL) {
        sfView_move(view, move);
        sfRenderWindow_setView(window, view);
        sfView_destroy(view);
    }
}

void manage_movement(game_t *game)
{
    sfVector2f move = {0.0, 0.0};

    if (can_entities_move(game->scene)) {
        if (game->player->moving && game->player->sprite != NULL) {
            move = move_player(game);
        }
        if (move.x != 0.0 || move.y != 0.0) {
            move_view(game->window, move);
        }
        for (size_t i = 0; game->npcs != NULL && game->npcs[i] != NULL; i++) {
            move_npc(game->npcs[i]);
        }
    }
}
