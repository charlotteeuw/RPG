/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** create_selection.c
*/

#include "my_def.h"
#include <stdlib.h>
#include "my.h"

static void skip_tuto(game_t *game, __attribute((unused)) button_t *button)
{
    activate_fade(game->fade);
    switch_to_spawn(game);
}

static void tuto(game_t *game, __attribute((unused)) button_t *button)
{
    activate_fade(game->fade);
    switch_to_tuto(game);
}

static void add_buttons(selection_t *character)
{
    button_t *button = NULL;

    character->buttons = NULL;
    button = create_button("SKIP TUTO", (sfVector2f){700, 780},
        (sfVector2f){0.8, 0.8}, skip_tuto);
    if (button != NULL) {
        append_to_list(&character->buttons, button);
    }
    button = create_button("START", (sfVector2f){1200, 780},
        (sfVector2f){0.8, 0.8}, tuto);
    if (button != NULL) {
        append_to_list(&character->buttons, button);
    }
    button = create_button("BACK", (sfVector2f){1700, 980},
        (sfVector2f){0.8, 0.8}, switch_to_title);
    if (button != NULL) {
        append_to_list(&character->buttons, button);
    }
}

static void create_woman(selection_t *selection)
{
    sfVector2f sprite_scale = {2, 2};
    sfVector2f sprite_pos = {780, 220};
    sfVector2f logo_scale = {0.1, 0.1};
    sfVector2f logo_pos = {850, 440};

    selection->woman_sprite = create_sprite("./assets/images/woman.png");
    if (selection->woman_sprite != NULL) {
        sfSprite_setPosition(selection->woman_sprite->sprite, sprite_pos);
        sfSprite_setScale(selection->woman_sprite->sprite, sprite_scale);
    }
    selection->woman_logo = create_sprite("./assets/images/woman_symbol.png");
    if (selection->woman_logo != NULL) {
        sfSprite_setPosition(selection->woman_logo->sprite, logo_pos);
        sfSprite_setScale(selection->woman_logo->sprite, logo_scale);
    }
}

static void create_man_and_name(selection_t *selection)
{
    sfVector2f sprite_scale = {0.8, 0.8};
    sfVector2f sprite_pos = {830, 190};
    sfVector2f logo_scale = {0.1, 0.1};
    sfVector2f logo_pos = {960, 440};

    selection->man_sprite = create_sprite("./assets/images/man.png");
    if (selection->man_sprite != NULL) {
        sfSprite_setPosition(selection->man_sprite->sprite, sprite_pos);
        sfSprite_setScale(selection->man_sprite->sprite, sprite_scale);
    }
    selection->man_logo = create_sprite("./assets/images/man_symbol.png");
    if (selection->man_logo != NULL) {
        sfSprite_setPosition(selection->man_logo->sprite, logo_pos);
        sfSprite_setScale(selection->man_logo->sprite, logo_scale);
    }
    selection->name = create_text("Name :", C_DARK_TEXT, 35);
    if (selection->name != NULL) {
        set_text_position(selection->name, (sfVector2f){800, 560});
    }
}

static sfRectangleShape *create_selection_rect(void)
{
    sfRectangleShape *rect = sfRectangleShape_create();
    sfVector2f position = {842, 435};
    sfVector2f size = {62, 65};

    if (rect != NULL) {
        sfRectangleShape_setSize(rect, size);
        sfRectangleShape_setPosition(rect, position);
        sfRectangleShape_setFillColor(rect, sfTransparent);
        sfRectangleShape_setOutlineThickness(rect, 2.0);
        sfRectangleShape_setOutlineColor(rect, C_DARK_TEXT);
    }
    return rect;
}

selection_t *create_selection(void)
{
    selection_t *selection = malloc(sizeof(selection_t));
    sfVector2f text_position = {900, 540};
    sfVector2f plate_scale = {3.5, 2.8};
    sfVector2f plate_pos = {452, 100};
    sfVector2f text_scale = {300, 50};

    if (selection != NULL) {
        selection->plate = create_sprite("./assets/images/plate.png");
        if (selection->plate != NULL && selection->plate->sprite != NULL) {
            sfSprite_setPosition(selection->plate->sprite, plate_pos);
            sfSprite_setScale(selection->plate->sprite, plate_scale);
        }
        selection->background = create_sprite("./assets/images/clouds.jpg");
        selection->textbox = create_textbox(text_position, text_scale, 30);
        selection->rect = create_selection_rect();
        create_man_and_name(selection);
        create_woman(selection);
        add_buttons(selection);
    }
    return selection;
}
