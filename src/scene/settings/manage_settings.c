/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** settings_create.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

static void create_framerate_buttons(list_t **head)
{
    button_t *button = create_button("30", (sfVector2f){890.0, 470.0},
        (sfVector2f){0.5, 1.0}, set_framerate_30);

    if (button != NULL) {
        append_to_list(head, button);
    }
    button = create_button("60", (sfVector2f){1020.0, 470.0},
        (sfVector2f){0.5, 1.0}, set_framerate_60);
    if (button != NULL) {
        append_to_list(head, button);
    }
    button = create_button("MAX", (sfVector2f){1150.0, 470.0},
        (sfVector2f){0.5, 1.0}, set_framerate_max);
    if (button != NULL) {
        append_to_list(head, button);
    }
}

static void create_window_buttons(list_t **head)
{
    button_t *button = create_button("FULLSCREEN", (sfVector2f){820.0, 620.0},
        (sfVector2f){1.0, 1.0}, set_fullscreen);

    if (button != NULL) {
        append_to_list(head, button);
    }
    button = create_button("WINDOWED", (sfVector2f){1100.0, 620.0},
        (sfVector2f){1.0, 1.0}, set_windowed);
    if (button != NULL) {
        append_to_list(head, button);
    }
}

static void create_settings_buttons(list_t **head)
{
    button_t *button = create_button("BACK", (sfVector2f){70.0, 1000.0},
        (sfVector2f){0.5, 1.0}, switch_to_title);

    if (button != NULL) {
        append_to_list(head, button);
    }
    button = create_button("HIDE", (sfVector2f){760.0, 470.0},
        (sfVector2f){0.5, 1.0}, switch_framerate);
    if (button != NULL) {
        append_to_list(head, button);
    }
    create_framerate_buttons(head);
    create_window_buttons(head);
}

static void create_settings_text(char *str, list_t **head, sfVector2f position)
{
    sfText *text = create_text(str, C_DARK_TEXT, 30);

    if (text != NULL) {
        set_text_position(text, position);
        append_to_list(head, text);
    }
}

static void create_settings_drawer(list_t **buttons, list_t **texts)
{
    create_settings_text("Sound", texts, (sfVector2f){960.0, 200.0});
    create_settings_text("Music", texts, (sfVector2f){960.0, 300.0});
    create_settings_text("Framerate", texts, (sfVector2f){960.0, 400.0});
    create_settings_text("Window style", texts, (sfVector2f){960.0, 550.0});
    create_settings_text("Keybinds", texts, (sfVector2f){960.0, 700.0});
    create_settings_text("Up", texts, (sfVector2f){700.0, 760.0});
    create_settings_text("Left", texts, (sfVector2f){700.0, 810.0});
    create_settings_text("Down", texts, (sfVector2f){700.0, 860.0});
    create_settings_text("Right", texts, (sfVector2f){700.0, 910.0});
    create_settings_text("Tool", texts, (sfVector2f){700.0, 960.0});
    create_settings_text("Inventory", texts, (sfVector2f){1000.0, 760.0});
    create_settings_text("Sprint", texts, (sfVector2f){1000.0, 810.0});
    create_settings_text("Quests", texts, (sfVector2f){1000.0, 860.0});
    create_settings_text("Pause", texts, (sfVector2f){1000.0, 910.0});
    create_settings_buttons(buttons);
}

static void create_settings_keybinds(void *buttons[MAX_KEYBINDS])
{
    sfVector2f position = {830.0, 760.0};
    sfVector2f scale = {0.6, 0.6};

    for (unsigned short i = 0; i < MAX_KEYBINDS; i++) {
        buttons[i] = create_button("", position, scale, update_keybind);
        if (buttons[i] != NULL) {
            position.y += 50.0;
        }
        if (buttons[i] != NULL && i == (unsigned short)(MAX_KEYBINDS / 2)) {
            position.x += 350.0;
            position.y = 760.0;
        }
    }
}

settings_t *create_settings(void)
{
    settings_t *new = malloc(sizeof(settings_t));
    sfVector2f size = {600.0, 15.0};

    if (new != NULL) {
        new->texts = NULL;
        new->buttons = NULL;
        new->fullscreen = true;
        new->plate = create_sprite("./assets/images/plate.png");
        if (new->plate != NULL) {
            sfSprite_setScale(new->plate->sprite, (sfVector2f){2.9, 3.5});
            center_sprite(new->plate->sprite);
            sfSprite_setPosition(new->plate->sprite, (sfVector2f){960, 540});
        }
        new->framerate = DEFAULT_FRAMERATE;
        new->sound = create_slider((sfVector2f){960.0, 250.0}, size);
        new->music = create_slider((sfVector2f){960.0, 350}, size);
        create_settings_drawer(&new->buttons, &new->texts);
        create_settings_keybinds(new->keybinds);
    }
    return new;
}

static void destroy_settings_drawer(settings_t *settings)
{
    for (enum e_keybinds i = 0; i < MAX_KEYBINDS; i++) {
        if (settings->keybinds[i] != NULL) {
            destroy_button(settings->keybinds[i]);
        }
    }
}

void destroy_settings(settings_t *settings)
{
    if (settings != NULL) {
        if (settings->plate != NULL) {
            destroy_sprite(settings->plate);
        }
        if (settings->sound != NULL) {
            destroy_slider(settings->sound);
        }
        if (settings->music != NULL) {
            destroy_slider(settings->music);
        }
        if (settings->buttons != NULL) {
            destroy_list(settings->buttons, destroy_button);
        }
        if (settings->texts != NULL) {
            destroy_list(settings->texts, destroy_text);
        }
        destroy_settings_drawer(settings);
        free(settings);
    }
}
