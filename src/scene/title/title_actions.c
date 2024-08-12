/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** actions_title.c
*/

#include "my.h"

void action_exit(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->window != NULL) {
        sfRenderWindow_close(game->window);
    }
}
