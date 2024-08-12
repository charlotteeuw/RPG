/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** slider.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

static void create_slider_rect(sfRectangleShape *bars[MAX_SLIDERS],
    sfVector2f position, sfVector2f size)
{
    sfVector2f hit_size = {.x = size.x + 20.0, .y = 2.0 * size.y};
    sfVector2f new_size = {.x = size.x / 2.0, .y = size.y};
    sfVector2f new_position = {.x = position.x - new_size.x, .y = position.y};

    bars[SLIDER_LEFT] = create_rect(new_position, size, C_IN_TEXTBOX);
    if (bars[SLIDER_LEFT] != NULL) {
        sfRectangleShape_setOutlineThickness(bars[SLIDER_LEFT], 1);
        center_rect(bars[SLIDER_LEFT], false, true);
    }
    bars[SLIDER_RIGHT] = create_rect(position, new_size, C_DARK_TEXT);
    if (bars[SLIDER_RIGHT] != NULL) {
        sfRectangleShape_setOutlineThickness(bars[SLIDER_RIGHT], 1);
        center_rect(bars[SLIDER_RIGHT], false, true);
    }
    bars[SLIDER_HITBOX] = create_rect(position, hit_size, sfTransparent);
    if (bars[SLIDER_HITBOX] != NULL) {
        center_rect(bars[SLIDER_HITBOX], true, true);
    }
}

slider_t *create_slider(sfVector2f position, sfVector2f size)
{
    slider_t *slider = malloc(sizeof(slider_t));
    float radius = size.y / 1.2;
    sfVector2f origin = {.x = radius, .y = radius};

    if (slider != NULL) {
        slider->cursor = sfCircleShape_create();
        if (slider->cursor != NULL) {
            sfCircleShape_setFillColor(slider->cursor, C_LIGHT_TEXT);
            sfCircleShape_setOutlineColor(slider->cursor, sfBlack);
            sfCircleShape_setOutlineThickness(slider->cursor, 1);
            sfCircleShape_setRadius(slider->cursor, radius);
            sfCircleShape_setOrigin(slider->cursor, origin);
            sfCircleShape_setPosition(slider->cursor, position);
        }
        create_slider_rect(slider->bars, position, size);
        slider->position = position;
        slider->active = sfFalse;
        slider->size = size;
    }
    return slider;
}

void render_slider(sfRenderWindow *window, slider_t *slider)
{
    for (size_t i = 0; i < MAX_SLIDERS; i++) {
        if (slider->bars[i] != NULL) {
            sfRenderWindow_drawRectangleShape(window, slider->bars[i], NULL);
        }
    }
    if (slider->cursor != NULL) {
        sfRenderWindow_drawCircleShape(window, slider->cursor, NULL);
    }
}

static void move_slider(slider_t *slider, float mouse)
{
    float len = slider->size.x / 2.0;
    sfVector2f new_size = {
        .x = slider->position.x + len - mouse, .y = slider->size.y
    };
    sfVector2f left = {
        .x = mouse - slider->position.x + len, .y = slider->size.y
    };
    sfVector2f new_position = {.x = mouse, .y = slider->position.y};
    sfVector2f new_cursor = {.x = mouse, .y = slider->position.y};

    if (slider->cursor != NULL) {
        sfCircleShape_setPosition(slider->cursor, new_cursor);
    }
    if (slider->bars[SLIDER_LEFT] != NULL) {
        sfRectangleShape_setSize(slider->bars[SLIDER_LEFT], left);
    }
    if (slider->bars[SLIDER_RIGHT] != NULL) {
        sfRectangleShape_setPosition(slider->bars[SLIDER_RIGHT], new_position);
        sfRectangleShape_setSize(slider->bars[SLIDER_RIGHT], new_size);
    }
}

static float is_exceeding(slider_t *slider, float *value, float mouse)
{
    sfFloatRect bounds = sfRectangleShape_getGlobalBounds(
        slider->bars[SLIDER_HITBOX]);
    sfVector2f position = sfCircleShape_getPosition(slider->cursor);
    float right = bounds.left + bounds.width;
    float new = mouse;

    if (position.x <= bounds.left && mouse <= bounds.left) {
        new = bounds.left;
    } else if (position.x >= right && mouse >= right) {
        new = right;
    }
    if (value != NULL) {
        *value = (new - bounds.left) / bounds.width;
    }
    return new;
}

void analyse_slider_events(slider_t *slider, sfVector2f mouse, float *value)
{
    sfBool in = sfFalse;
    float x = 0.0;

    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        if (!slider->active) {
            in = is_in_rect(slider->bars[SLIDER_HITBOX], mouse.x, mouse.y);
        }
        if (in) {
            slider->active = sfTrue;
        }
    } else if (slider->active) {
        slider->active = sfFalse;
    }
    if (slider->active) {
        x = is_exceeding(slider, value, mouse.x);
        move_slider(slider, x);
    }
}

void destroy_slider(slider_t *slider)
{
    if (slider != NULL) {
        if (slider->bars[SLIDER_LEFT] != NULL) {
            sfRectangleShape_destroy(slider->bars[SLIDER_LEFT]);
        }
        if (slider->bars[SLIDER_RIGHT] != NULL) {
            sfRectangleShape_destroy(slider->bars[SLIDER_RIGHT]);
        }
        if (slider->bars[SLIDER_HITBOX] != NULL) {
            sfRectangleShape_destroy(slider->bars[SLIDER_HITBOX]);
        }
        if (slider->cursor != NULL) {
            sfCircleShape_destroy(slider->cursor);
        }
        free(slider);
    }
}
