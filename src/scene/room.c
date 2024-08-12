/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** room.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

static void analyse_interaction(game_t *game, sfEvent *event, int *interaction)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = {center.x - 100, center.y + 370};
    static int do_once = 1;

    game->room->is_dialogue = 1;
    if (game->room->dialogue != NULL) {
        game->room->text =
            handle_dialogue(game, event, pos, game->room->text);
    }
    if (game->room->text == NULL && do_once == 1) {
        *interaction = 0;
        game->room->passed = 1;
        game->room->is_dialogue = 0;
        game->player->health += 30;
        game->player->experience += 20;
        game->player->quests->third_quest = 1;
        do_once = 0;
        add_item_to_inventory(game->player->inventory, ITEM_POTION, 1);
    }
}

void analyse_room_events(game_t *game, sfEvent *event)
{
    sfVector2f position = sfSprite_getPosition(game->player->sprite->sprite);
    static int interaction = 0;

    if ((position.x >= 700 && position.x <= 970) &&
        (position.y >= 300 && position.y <= 620) &&
        game->keybinds[BIND_TOOL] == event->key.code &&
        event->type == sfEvtKeyReleased) {
        interaction = 1;
    }
    if (interaction == 1 && game->day >= 2)
        analyse_interaction(game, event, &interaction);
    if (position.y >= 1004)
        start_game(game, (sfVector2f){5249.0, 8419.0});
}

static void draw_dialogue_assets2(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->room->icon != NULL && game->room->is_dialogue == 1
        && game->day >= 2) {
        sfSprite_setPosition(game->room->icon->sprite,
            (sfVector2f){bottom.x + 40, bottom.y + 50});
        sfRenderWindow_drawSprite(window, game->room->icon->sprite, NULL);
    }
    if (game->room->is_dialogue == 1 && game->day >= 2) {
        draw_dialogue(game->room->text, window);
    }
}

static void draw_dialogue_assets(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->room->passed == 1) {
        return;
    }
    if (game->room->dialogue != NULL && game->room->is_dialogue == 1
        && game->day >= 2) {
        sfSprite_setPosition(game->room->dialogue->sprite, bottom);
        sfRenderWindow_drawSprite(window, game->room->dialogue->sprite,
            NULL);
    }
    draw_dialogue_assets2(window, game, center);
}

void render_room(game_t *game)
{
    sfRenderWindow *window = game->window;
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);

    if (game->room->bg != NULL)
        sfRenderWindow_drawSprite(window, game->room->bg->sprite, NULL);
    if (game->player->sprite != NULL)
        sfRenderWindow_drawSprite(window, game->player->sprite->sprite, NULL);
    if (game->cat != NULL && game->cat_is_dead == 0)
        sfRenderWindow_drawSprite(window, game->cat->sprite, NULL);
    if (game->room->npc != NULL)
        sfRenderWindow_drawSprite(window, game->room->npc->sprite, NULL);
    draw_dialogue_assets(window, game, center);
}

void destroy_room(room_t *room)
{
    if (room->bg != NULL) {
        destroy_sprite(room->bg);
    }
    if (room->npc != NULL) {
        destroy_sprite(room->npc);
    }
    if (room->dialogue != NULL) {
        destroy_sprite(room->dialogue);
    }
    if (room->icon != NULL) {
        destroy_sprite(room->icon);
    }
    free(room);
}

room_t *create_room(void)
{
    room_t *room = malloc(sizeof(room_t));

    if (room != NULL) {
        room->passed = 0;
        room->bg = create_sprite("./assets/images/nattys_room.png");
        room->npc = create_sprite("./assets/images/Natty.png");
        room->collision = sfImage_createFromFile(
            "./assets/images/nattys_room_collision.png"
        );
        room->dialogue = create_sprite("./assets/images/dialogue.png");
        room->icon = create_sprite("./assets/images/Natty.png");
        sfSprite_setScale(room->npc->sprite, (sfVector2f){6, 6});
        sfSprite_setScale(room->dialogue->sprite, (sfVector2f){3, 3});
        sfSprite_setScale(room->icon->sprite, (sfVector2f){5, 5});
    }
    return room;
}

void switch_to_room(game_t *game)
{
    game->scene = SCENE_ROOM;
    game->room->text = create_dialogue_text("./assets/dialogue/quest3.txt",
        game->player->name);
    sfSprite_setPosition(game->player->sprite->sprite, (sfVector2f){810, 600});
    sfSprite_setPosition(game->room->npc->sprite, (sfVector2f){920, 445});
    setposition_view(game->window, (sfVector2f){810, 600});
}
