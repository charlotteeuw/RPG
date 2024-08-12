/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** main.c
*/

#include <stdlib.h>
#include "my.h"

const char *title_names[4] = {"NEW", "RESUME", "SETTINGS", "EXIT"};

void (*title_actions[4])(game_t *, button_t *) = {
    switch_selection, switch_to_resume, switch_to_settings, action_exit
};

static void create_title_buttons(list_t **head)
{
    sfVector2f position = {960.0, 540.0};
    sfVector2f scale = {1.5, 1.5};
    button_t *button = NULL;

    for (unsigned short i = 0; i < 4; i++) {
        button = create_button(title_names[i],
            position, scale, title_actions[i]);
        if (button != NULL) {
            append_to_list(head, button);
            position.y += 120.0;
        }
    }
}

title_t *create_title(void)
{
    title_t *new = malloc(sizeof(title_t));
    sfVector2f logo = {590.0, 120.0};

    if (new != NULL) {
        new->buttons = NULL;
        new->music = create_music("./assets/sounds/title.ogg");
        new->logo = create_sprite("./assets/images/logo.png");
        if (new->logo != NULL && new->logo->sprite != NULL) {
            sfSprite_setPosition(new->logo->sprite, logo);
        }
        create_title_buttons(&new->buttons);
    }
    return new;
}

void render_title(game_t *game)
{
    sfRenderWindow *window = game->window;
    title_t *title = game->title;

    if (window != NULL && title != NULL) {
        if (game->bg != NULL) {
            sfRenderWindow_drawSprite(window, game->bg->sprite, NULL);
        }
        if (title->logo != NULL) {
            sfRenderWindow_drawSprite(window, title->logo->sprite, NULL);
        }
        for (list_t *temp = title->buttons; temp != NULL; temp = temp->next) {
            render_button(window, temp->data);
        }
    }
}

void analyse_title_events(game_t *game, sfEvent *event)
{
    for (list_t *temp = game->title->buttons;
        temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            analyse_button_events(game, event, temp->data);
        }
    }
}

void destroy_title(title_t *title)
{
    if (title->logo != NULL) {
        destroy_sprite(title->logo);
    }
    if (title->music != NULL) {
        sfMusic_destroy(title->music);
    }
    if (title->buttons != NULL) {
        destroy_list(title->buttons, destroy_button);
    }
    free(title);
}

void switch_to_title(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->title != NULL) {
        if (game->title->music != NULL &&
            sfMusic_getStatus(game->title->music) != sfPlaying) {
            sfMusic_play(game->title->music);
        }
        for (list_t *temp = game->title->buttons;
            temp != NULL; temp = temp->next) {
            reset_button(temp->data);
        }
        game->scene = SCENE_TITLE;
    }
}
