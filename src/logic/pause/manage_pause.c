/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** pause.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

const char *pause_names[4] = {"RESUME", "SAVE", "SETTINGS", "EXIT"};

void (*pause_actions[4])(game_t *, button_t *) = {
    pause_resume, save_game, NULL, pause_quit
};

static void create_pause_buttons(list_t **head)
{
    sfVector2f position = {0.5, 0.4};
    sfVector2f scale = {1.5, 1.5};
    button_t *button = NULL;

    for (unsigned short i = 0; i < 4; i++) {
        button = create_button(pause_names[i],
            position, scale, pause_actions[i]);
        if (button != NULL) {
            sfText_setPosition(button->text, position);
            append_to_list(head, button);
            position.y += 0.10;
        }
    }
}

static sprite_t *create_plate(void)
{
    sprite_t *plate = create_sprite("./assets/images/plate.png");
    sfVector2f position = {0.5, 0.5};
    sfVector2f scale = {2.5, 2.5};

    if (plate != NULL && plate->sprite != NULL) {
        center_sprite(plate->sprite);
        sfSprite_setPosition(plate->sprite, position);
        sfSprite_setScale(plate->sprite, scale);
    }
    return plate;
}

pause_t *create_pause(void)
{
    pause_t *pause = malloc(sizeof(pause_t));
    sfVector2f position = {0.415, 0.25};

    if (pause != NULL) {
        pause->text = create_text("Game paused", C_DARK_TEXT, 50);
        if (pause->text != NULL) {
            sfText_setPosition(pause->text, position);
        }
        pause->buttons = NULL;
        pause->plate = create_plate();
        create_pause_buttons(&pause->buttons);
        pause->is_open = false;
    }
    return pause;
}

void render_pause(sfRenderWindow *window, pause_t *pause)
{
    if (window != NULL && pause != NULL && pause->is_open) {
        if (pause->plate != NULL && pause->plate->sprite != NULL) {
            view_dynamic_drawsprite(window, pause->plate->sprite);
        }
        if (pause->text != NULL) {
            view_dynamic_drawtext(window, pause->text);
        }
        for (list_t *temp = pause->buttons; temp != NULL; temp = temp->next) {
            view_render_button(window, temp->data);
        }
    }
}

static void analyse_pause_buttons(game_t *game, sfEvent *event)
{
    for (list_t *temp = game->player->pause->buttons; temp != NULL;
        temp = temp->next) {
        if (temp->data != NULL) {
            view_analyse_button_events(game, event, temp->data);
        }
    }
}

void analyse_pause_events(game_t *game, sfEvent *event)
{
    if (event->type != sfEvtKeyReleased) {
        analyse_pause_buttons(game, event);
    } else {
        if (event->key.code != game->keybinds[BIND_PAUSE]){
            return;
        }
        game->player->pause->is_open = !game->player->pause->is_open;
        switch_player_movement(game->player, SWITCH_MOVING);
        if (game->player->quests->is_open) {
            game->player->quests->is_open = false;
        }
        if (game->player->inventory->is_open) {
            game->player->inventory->is_open = false;
        }
    }
}

void destroy_pause(pause_t *pause)
{
    if (pause != NULL) {
        if (pause->buttons != NULL) {
            destroy_list(pause->buttons, destroy_button);
        }
        if (pause->plate != NULL) {
            destroy_sprite(pause->plate);
        }
        if (pause->text != NULL) {
            sfText_destroy(pause->text);
        }
    }
}
