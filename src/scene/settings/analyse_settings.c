/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** settings_events.c
*/

#include <string.h>
#include "my.h"

static void analyse_sounds_settings(game_t *game)
{
    if (game->settings->sound != NULL && game->settings->music != NULL) {
        if (!game->settings->sound->active) {
            analyse_slider_events(game->settings->music,
                game->mouse, &game->volumes[VOLUME_MUSIC]);
            update_volumes(game);
        }
        if (!game->settings->music->active) {
            analyse_slider_events(game->settings->sound,
                game->mouse, &game->volumes[VOLUME_SOUND]);
            update_volumes(game);
        }
    }
}

void analyse_settings_events(game_t *game, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape) {
        sfSound_play(game->sounds[SOUND_CLICK]->play);
        switch_to_title(game, NULL);
    }
    for (list_t *temp = game->settings->buttons;
        temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            analyse_button_events(game, event, temp->data);
        }
    }
    for (enum e_keybinds i = 0; i < MAX_KEYBINDS; i++) {
        if (game->settings->keybinds[i] != NULL) {
            analyse_button_events(game, event, game->settings->keybinds[i]);
        }
    }
    analyse_sounds_settings(game);
}

static void update_keybinds_buttons(game_t *game)
{
    button_t *button = NULL;

    for (enum e_keybinds i = 0; i < MAX_KEYBINDS; i++) {
        button = game->settings->keybinds[i];
        if (button != NULL && button->text != NULL && button->frame != NULL) {
            sfText_setString(button->text, keys_name[game->keybinds[i]]);
            button_center_text(button->frame->sprite, button->text, 5.0);
        }
    }
}

static bool retrieve_key(unsigned short *keybinds, enum e_keybinds ref)
{
    for (sfKeyCode i = 0; i < sfKeyCount; i++) {
        if (sfKeyboard_isKeyPressed(i)) {
            keybinds[ref] = i;
            return true;
        }
    }
    return false;
}

void update_keybind(game_t *game, button_t *button)
{
    enum e_keybinds ref = 0;

    for (enum e_keybinds i = 0; i < MAX_KEYBINDS; i++) {
        if (game->settings->keybinds[i] == button) {
            ref = i;
            break;
        }
    }
    while (true) {
        if (retrieve_key(game->keybinds, ref)) {
            break;
        }
        sfSleep(sfSeconds(0.1));
    }
    update_keybinds_buttons(game);
    save_keybinds(game->keybinds);
}

void switch_to_settings(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL && game->settings != NULL) {
        if (game->title != NULL && game->title->music != NULL &&
            sfMusic_getStatus(game->title->music) != sfPlaying) {
            sfMusic_play(game->title->music);
        }
        for (list_t *temp = game->settings->buttons;
            temp != NULL; temp = temp->next) {
            reset_button(temp->data);
        }
        update_keybinds_buttons(game);
        game->scene = SCENE_SETTINGS;
    }
}
