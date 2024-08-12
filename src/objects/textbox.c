/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** textbox.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

textbox_t *create_textbox(sfVector2f position,
    sfVector2f size, unsigned int font_size)
{
    sfVector2f text_position = {position.x + 5.0, position.y};
    textbox_t *textbox = malloc(sizeof(textbox_t));

    if (textbox != NULL) {
        textbox->text = create_text("", C_DARK_TEXT, font_size);
        if (textbox->text != NULL) {
            sfText_setPosition(textbox->text, text_position);
        }
        textbox->frame = sfRectangleShape_create();
        if (textbox->frame != NULL) {
            sfRectangleShape_setSize(textbox->frame, size);
            sfRectangleShape_setPosition(textbox->frame, position);
            sfRectangleShape_setFillColor(textbox->frame, C_IN_TEXTBOX);
            sfRectangleShape_setOutlineThickness(textbox->frame, 2);
            sfRectangleShape_setOutlineColor(textbox->frame, C_OUT_TEXTBOX);
        }
        textbox->active = sfFalse;
    }
    return textbox;
}

static sfBool is_exceeding(textbox_t *textbox)
{
    sfVector2f rect_size = sfRectangleShape_getSize(textbox->frame);
    sfFloatRect text_bounds = sfText_getGlobalBounds(textbox->text);

    return (text_bounds.width + 10.0 > rect_size.x);
}

static void update_textbox(textbox_t *textbox, sfUint32 unicode)
{
    char const *text = sfText_getString(textbox->text);
    char *str = my_strdup(text);
    size_t len = 0;

    if (!str) {
        return;
    }
    len = my_strlen(str);
    if (unicode != '\b') {
        if (!is_exceeding(textbox)) {
            str = realloc(str, len + 2);
            str[len] = unicode;
            str[len + 1] = '\0';
        }
    } else if (len > 0) {
        str[len - 1] = '\0';
    }
    sfText_setString(textbox->text, str);
    free(str);
}

bool analyse_textbox_events(game_t *game, sfEvent *event, textbox_t *textbox)
{
    switch (event->type) {
        case sfEvtMouseButtonReleased:
            textbox->active = is_in_rect(textbox->frame,
                game->mouse.x, game->mouse.y);
            return false;
        case sfEvtTextEntered:
            if (textbox->active) {
                update_textbox(textbox, event->text.unicode);
            }
            return true;
        default:
            break;
    }
    return false;
}

void render_textbox(sfRenderWindow *window, textbox_t *textbox)
{
    if (textbox != NULL) {
        sfRenderWindow_drawRectangleShape(window, textbox->frame, NULL);
        sfRenderWindow_drawText(window, textbox->text, NULL);
    }
}

void destroy_textbox(textbox_t *textbox)
{
    if (textbox != NULL) {
        if (textbox->frame != NULL) {
            sfRectangleShape_destroy(textbox->frame);
        }
        if (textbox->text != NULL) {
            sfText_destroy(textbox->text);
        }
        free(textbox);
    }
}
