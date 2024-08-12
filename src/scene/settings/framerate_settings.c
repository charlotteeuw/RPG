/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** framerate.c
*/

#include "my.h"

void switch_framerate(game_t *game, button_t *button)
{
    if (game != NULL) {
        if (game->framerate_displayed) {
            sfText_setString(button->text, "SHOW");
            button_center_text(button->frame->sprite, button->text, 10.0);
        } else {
            sfText_setString(button->text, "HIDE");
            button_center_text(button->frame->sprite, button->text, 10.0);
        }
        game->framerate_displayed = !game->framerate_displayed;
    }
}

void set_framerate_30(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->window != NULL) {
        sfRenderWindow_setFramerateLimit(game->window, 30);
        if (game->settings != NULL) {
            game->settings->framerate = 30;
        }
    }
}

void set_framerate_60(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->window != NULL) {
        sfRenderWindow_setFramerateLimit(game->window, 60);
        if (game->settings != NULL) {
            game->settings->framerate = 60;
        }
    }
}

void set_framerate_max(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->window != NULL) {
        sfRenderWindow_setFramerateLimit(game->window, 0);
        if (game->settings != NULL) {
            game->settings->framerate = 0;
        }
    }
}
