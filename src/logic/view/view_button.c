/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** button.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

static void button_hover(sfRenderWindow *window,
    button_t *button, sfVector2f mouse)
{
    sfBool in = view_is_in_sprite(window,
        button->frame->sprite, mouse.x, mouse.y);

    if (in && button->state != BUTTON_HOVERED) {
        sfSprite_setTextureRect(button->frame->sprite, shapes[BUTTON_HOVERED]);
        if (button->text != NULL) {
            sfText_setColor(button->text, C_LIGHT_TEXT);
        }
        button->state = BUTTON_HOVERED;
    }
    if (!in) {
        reset_button(button);
    }
}

static void button_pressed(sfRenderWindow *window,
    button_t *button, sfVector2f mouse)
{
    sfBool in = view_is_in_sprite(window,
        button->frame->sprite, mouse.x, mouse.y);

    if (in && button->state != BUTTON_PRESSED) {
        sfSprite_setTextureRect(button->frame->sprite, shapes[BUTTON_PRESSED]);
        if (button->text != NULL) {
            sfText_setColor(button->text, C_LIGHT_TEXT);
        }
        button->state = BUTTON_PRESSED;
    }
}

static void button_released(game_t *game, button_t *button)
{
    sfBool in = view_is_in_sprite(game->window,
        button->frame->sprite, game->mouse.x, game->mouse.y);

    if (in) {
        if (button->action != NULL) {
            button->action(game, button);
        }
        button_hover(game->window, button, game->mouse);
    } else {
        reset_button(button);
    }
}

void view_analyse_button_events(game_t *game, sfEvent *event, button_t *button)
{
    if (button->frame != NULL && button->frame->sprite != NULL) {
        switch (event->type) {
            case sfEvtMouseMoved:
                button_hover(game->window, button, game->mouse);
                break;
            case sfEvtMouseButtonPressed:
                button_pressed(game->window, button, game->mouse);
                break;
            case sfEvtMouseButtonReleased:
                button_released(game, button);
                break;
            default:
                break;
        }
    }
}

void view_render_button(sfRenderWindow *window, button_t *button)
{
    if (button != NULL) {
        if (button->frame != NULL && button->frame->sprite != NULL) {
            view_dynamic_drawsprite(window, button->frame->sprite);
        }
        if (button->text != NULL) {
            view_dynamic_drawtext(window, button->text);
        }
    }
}
