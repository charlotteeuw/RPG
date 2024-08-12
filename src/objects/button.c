/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** button.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

const sfIntRect shapes[3] = {
    {.left = 16, .top = 12, .width = 225, .height = 60},
    {.left = 265, .top = 12, .width = 225, .height = 60},
    {.left = 500, .top = 12, .width = 225, .height = 60}
};

button_t *create_button(char const *text, sfVector2f position,
    sfVector2f scale, void (*action)(game_t *, struct s_button *))
{
    button_t *new = malloc(sizeof(button_t));

    if (new != NULL) {
        new->frame = create_sprite("./assets/images/button.png");
        if (new->frame != NULL && new->frame->sprite != NULL) {
            sfSprite_setTextureRect(new->frame->sprite, shapes[BUTTON_NONE]);
            center_sprite(new->frame->sprite);
            sfSprite_setPosition(new->frame->sprite, position);
            sfSprite_setScale(new->frame->sprite, scale);
        }
        new->text = create_text(text, C_DARK_TEXT, scale.y * 30 / 1.0);
        if (new->text != NULL) {
            set_text_position(new->text, position);
        }
        new->state = BUTTON_NONE;
        new->action = action;
    }
    return new;
}

void reset_button(button_t *button)
{
    if (button != NULL && button->state != BUTTON_NONE) {
        sfSprite_setTextureRect(button->frame->sprite, shapes[BUTTON_NONE]);
        if (button->text != NULL) {
            sfText_setColor(button->text, C_DARK_TEXT);
        }
        button->state = BUTTON_NONE;
    }
}

static void button_hover(button_t *button, sfVector2f mouse)
{
    sfBool in = is_in_sprite(button->frame->sprite, mouse.x, mouse.y);

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

static void button_pressed(button_t *button, sfVector2f mouse)
{
    sfBool in = is_in_sprite(button->frame->sprite, mouse.x, mouse.y);

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
    sfBool in = is_in_sprite(button->frame->sprite,
        game->mouse.x, game->mouse.y);

    if (in) {
        if (button->action != NULL) {
            button->action(game, button);
        }
        button_hover(button, game->mouse);
    } else {
        reset_button(button);
    }
}

void analyse_button_events(game_t *game, sfEvent *event, button_t *button)
{
    if (!button) {
        return;
    }
    if (button->frame != NULL && button->frame->sprite != NULL) {
        switch (event->type) {
            case sfEvtMouseMoved:
                button_hover(button, game->mouse);
                break;
            case sfEvtMouseButtonPressed:
                button_pressed(button, game->mouse);
                break;
            case sfEvtMouseButtonReleased:
                button_released(game, button);
                break;
            default:
                break;
        }
    }
}

void render_button(sfRenderWindow *window, button_t *button)
{
    if (button != NULL) {
        if (button->frame != NULL && button->frame->sprite != NULL) {
            sfRenderWindow_drawSprite(window, button->frame->sprite, NULL);
        }
        if (button->text != NULL) {
            sfRenderWindow_drawText(window, button->text, NULL);
        }
    }
}

void destroy_button(void *ptr)
{
    button_t *button = ptr;

    if (button != NULL) {
        if (button->frame != NULL) {
            destroy_sprite(button->frame);
        }
        if (button->text != NULL) {
            sfText_destroy(button->text);
        }
        free(button);
    }
}
