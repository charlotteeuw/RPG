/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** new.c
*/

#include <stdlib.h>
#include "my.h"

static void update_gender(selection_t *selection,
    sfEvent *event, sfVector2f *mouse, bool *male)
{
    sfVector2f woman_pos = {842, 435};
    sfVector2f man_pos = {955, 435};
    sfBool in = sfFalse;

    if (event->type != sfEvtMouseButtonReleased) {
        return;
    }
    in = is_in_sprite(selection->man_logo->sprite, mouse->x, mouse->y);
    if (in) {
        sfRectangleShape_setPosition(selection->rect, man_pos);
        *male = true;
    } else {
        in = is_in_sprite(selection->woman_logo->sprite, mouse->x, mouse->y);
        if (in) {
            sfRectangleShape_setPosition(selection->rect, woman_pos);
            *male = false;
        }
    }
}

void analyse_selection_events(game_t *game, sfEvent *event)
{
    const char *str = NULL;

    if (analyse_textbox_events(game, event, game->selection->textbox)) {
        if (game->player->name != NULL) {
            free(game->player->name);
        }
        str = sfText_getString(game->selection->textbox->text);
        if (str != NULL) {
            game->player->name = my_strdup(str);
        }
    }
    update_gender(game->selection, event, &game->mouse, &game->player->male);
    for (list_t *temp = game->selection->buttons;
        temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            analyse_button_events(game, event, temp->data);
        }
    }
}

static void render_character(sfRenderWindow *window,
    selection_t *selection, bool male)
{
    if (male && selection->man_sprite != NULL) {
        sfRenderWindow_drawSprite(window, selection->man_sprite->sprite, NULL);
    } else {
        if (selection->woman_sprite != NULL) {
            sfRenderWindow_drawSprite(window,
                selection->woman_sprite->sprite, NULL);
        }
    }
    if (selection->man_logo != NULL) {
        sfRenderWindow_drawSprite(window, selection->man_logo->sprite, NULL);
    }
    if (selection->woman_logo != NULL) {
        sfRenderWindow_drawSprite(window, selection->woman_logo->sprite, NULL);
    }
    if (selection->rect != NULL) {
        sfRenderWindow_drawRectangleShape(window, selection->rect, NULL);
    }
}

void render_selection(game_t *game)
{
    selection_t *selection = game->selection;
    sfRenderWindow *window = game->window;

    if (selection->background != NULL) {
        sfRenderWindow_drawSprite(window, selection->background->sprite, NULL);
    }
    if (selection->plate != NULL) {
        sfRenderWindow_drawSprite(window, selection->plate->sprite, NULL);
    }
    for (list_t *temp = selection->buttons; temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            render_button(window, temp->data);
        }
    }
    if (selection->name != NULL) {
        sfRenderWindow_drawText(window, selection->name, NULL);
    }
    render_character(window, selection, game->player->male);
    render_textbox(window, selection->textbox);
}

void destroy_selection(selection_t *scene)
{
    if (scene->background != NULL) {
        destroy_sprite(scene->background);
    }
    if (scene->woman_logo != NULL) {
        destroy_sprite(scene->woman_logo);
    }
    if (scene->man_logo != NULL) {
        destroy_sprite(scene->man_logo);
    }
    if (scene->man_sprite != NULL) {
        destroy_sprite(scene->man_sprite);
    }
    if (scene->woman_sprite != NULL) {
        destroy_sprite(scene->woman_sprite);
    }
    if (scene->rect != NULL) {
        sfRectangleShape_destroy(scene->rect);
    }
    free(scene);
}

void switch_selection(game_t *game, __attribute__((unused)) button_t *button)
{
    if (game != NULL) {
        if (game->player != NULL && game->player->inventory != NULL) {
            game->player->inventory->is_open = false;
        }
        if (game->player != NULL && game->player->quests != NULL) {
            game->player->quests->is_open = false;
        }
        if (game->player != NULL && game->player->pause != NULL) {
            game->player->pause->is_open = false;
        }
        game->scene = SCENE_SELECTION;
    }
}
