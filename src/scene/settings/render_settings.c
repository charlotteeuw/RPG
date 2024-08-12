/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** settings_tools.c
*/

#include <stdlib.h>
#include "my.h"

static void render_settings_drawer(sfRenderWindow *window,
    settings_t *settings)
{
    for (list_t *temp = settings->texts; temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            sfRenderWindow_drawText(window, temp->data, NULL);
        }
    }
    for (list_t *temp = settings->buttons; temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            render_button(window, temp->data);
        }
    }
    for (enum e_keybinds i = 0; i < MAX_KEYBINDS; i++) {
        if (settings->keybinds[i] != NULL) {
            render_button(window, settings->keybinds[i]);
        }
    }
}

void render_settings(game_t *game)
{
    settings_t *settings = game->settings;
    sfRenderWindow *window = game->window;

    if (settings != NULL && window != NULL) {
        if (game->bg != NULL) {
            sfRenderWindow_drawSprite(window, game->bg->sprite, NULL);
        }
        if (settings->plate != NULL && settings->plate->sprite != NULL) {
            sfRenderWindow_drawSprite(window, settings->plate->sprite, NULL);
        }
        if (settings->sound != NULL) {
            render_slider(window, settings->sound);
        }
        if (settings->music != NULL) {
            render_slider(window, settings->music);
        }
        render_settings_drawer(window, settings);
    }
}
