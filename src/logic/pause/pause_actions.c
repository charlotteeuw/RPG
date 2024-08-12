/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** pause_actions.c
*/

#include "my.h"

void pause_resume(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->player != NULL && game->player->pause != NULL) {
        switch_player_movement(game->player, SWITCH_MOVING);
        game->player->pause->is_open = false;
    }
}

void pause_quit(game_t *game, button_t *button)
{
    sfVector2f view_pos = {960.0, 540.0};

    if (game != NULL && game->player != NULL && game->player->pause != NULL) {
        setposition_view(game->window, view_pos);
        reset_menu_state(game->player);
        switch_to_title(game, button);
        activate_fade(game->fade);
    }
}
