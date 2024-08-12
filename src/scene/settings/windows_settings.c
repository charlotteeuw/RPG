/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** style_settings.c
*/

#include "my.h"

void set_fullscreen(game_t *game, __attribute__((unused)) button_t *button)
{
    sfRenderWindow *new = NULL;
    unsigned int framerate = 0;

    if (game != NULL && game->settings != NULL && game->window != NULL) {
        if (!game->settings->fullscreen) {
            framerate = game->settings->framerate;
            new = create_window(sfFullscreen, 1920, 1080, framerate);
        }
        if (new != NULL) {
            sfRenderWindow_destroy(game->window);
            game->settings->fullscreen = true;
            game->window = new;
        }
    }
}

void set_windowed(game_t *game, __attribute__((unused)) button_t *button)
{
    sfRenderWindow *new = NULL;
    unsigned int framerate = 0;

    if (game != NULL && game->window != NULL && game->settings != NULL) {
        if (game->settings->fullscreen) {
            framerate = game->settings->framerate;
            new = create_window(sfDefaultStyle, 1920, 1080, framerate);
        }
        if (new != NULL) {
            sfRenderWindow_destroy(game->window);
            game->settings->fullscreen = false;
            game->window = new;
        }
    }
}
