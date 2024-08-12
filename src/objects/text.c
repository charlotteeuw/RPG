/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** text.c
*/

#include "my_def.h"
#include "my.h"

void set_text_position(sfText *text, sfVector2f position)
{
    sfFloatRect bounds = sfText_getGlobalBounds(text);
    sfVector2f new_position = {
        .x = position.x - bounds.left,
        .y = position.y - bounds.top
    };
    sfVector2f origin = {
        .x = bounds.width / 2,
        .y = bounds.height / 2
    };

    sfText_setOrigin(text, origin);
    sfText_setPosition(text, new_position);
}

void button_center_text(sfSprite *sprite, sfText *text, float offset)
{
    sfVector2f position = sfSprite_getPosition(sprite);
    sfFloatRect bounds = sfText_getLocalBounds(text);
    sfVector2f origin = {
        .x = bounds.width / 2.0,
        .y = bounds.height / 2.0
    };

    position.y -= offset;
    sfText_setOrigin(text, origin);
    sfText_setPosition(text, position);
}

void center_text_origin(sfText *text)
{
    sfFloatRect bounds = sfText_getLocalBounds(text);
    sfVector2f origin = {
        .x = bounds.width / 2,
        .y = bounds.height / 2
    };

    sfText_setOrigin(text, origin);
}

sfText *create_text(char const *str, sfColor color, unsigned int size)
{
    sfText *text = sfText_create();
    static sfBool first = sfTrue;
    static sfFont *font = NULL;

    if (first) {
        font = sfFont_createFromFile("./assets/fonts/merriweather.ttf");
        first = sfFalse;
    }
    if (text != NULL && font != NULL) {
        sfText_setCharacterSize(text, size);
        sfText_setColor(text, color);
        sfText_setString(text, str);
        sfText_setFont(text, font);
    }
    return text;
}

void destroy_text(void *ptr)
{
    sfText *text = ptr;

    if (text != NULL) {
        sfText_destroy(text);
    }
}
