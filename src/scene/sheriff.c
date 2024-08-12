/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** sheriff.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

static void set_end_of_interaction(game_t *game, int *dialogue,
    int *interaction)
{
    static int do_once = 1;

    if (game->sheriff->text == NULL && do_once == 1) {
        game->sheriff->passed = 1;
        *dialogue = 0;
        *interaction = 0;
        game->sheriff->is_dialogue = 0;
        game->player->experience += 20;
        game->player->quests->second_quest = 1;
        add_item_to_inventory(game->player->inventory, ITEM_SWORD, 1);
        game->player->damage += 20;
        do_once = 0;
    }
}

static void analyse_first_interaction(game_t *game, sfEvent *event,
    int *dialogue, int *interaction)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f bottom = {center.x - 300, center.y + 300};
    sfVector2f pos = {bottom.x + 400, bottom.y + 100};

    if (game->sheriff->passed == 1)
        return;
    game->sheriff->is_dialogue = 1;
    if (game->sheriff->dialogue != NULL)
        game->sheriff->text =
            handle_dialogue(game, event, pos, game->sheriff->text);
    set_end_of_interaction(game, dialogue, interaction);
}

void analyse_sheriff_events(game_t *game, sfEvent *event)
{
    sfVector2f position = sfSprite_getPosition(game->player->sprite->sprite);
    static int dialogue = 1;
    static int interaction = 0;

    if ((position.x >= 800 && position.x <= 950) &&
        (position.y >= 580 && position.y <= 620) &&
        game->keybinds[BIND_TOOL] == event->key.code &&
        event->type == sfEvtKeyReleased) {
            interaction = 1;
    }
    if (dialogue == 1 && interaction == 1 && game->day == 2)
        analyse_first_interaction(game, event, &dialogue, &interaction);
    if (position.y >= 1004)
        start_game(game, (sfVector2f){6804.0, 8487.0});
}

static void draw_dialogue_assets2(sfRenderWindow *window, game_t *game,
    sfVector2f center, int dialogue)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->sheriff->icon != NULL && game->sheriff->is_dialogue == 1
        && dialogue == 1 && game->day == 2) {
        sfSprite_setPosition(game->sheriff->icon->sprite,
            (sfVector2f){bottom.x + 40, bottom.y + 50});
        sfRenderWindow_drawSprite(window, game->sheriff->icon->sprite, NULL);
    }
    if (game->sheriff->is_dialogue == 1 && dialogue == 1 && game->day == 2) {
        draw_dialogue(game->sheriff->text, window);
    }
}

static void draw_dialogue_assets(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};
    static int dialogue = 1;

    if (game->sheriff->passed == 1)
        return;
    if (!game->sheriff->is_dialogue)
        dialogue = 0;
    else
        dialogue = 1;
    if (game->sheriff->dialogue != NULL && game->sheriff->is_dialogue == 1
        && dialogue == 1 && game->day == 2) {
        sfSprite_setPosition(game->sheriff->dialogue->sprite, bottom);
        sfRenderWindow_drawSprite(window, game->sheriff->dialogue->sprite,
            NULL);
    }
    draw_dialogue_assets2(window, game, center, dialogue);
}

void render_sheriff(game_t *game)
{
    sfRenderWindow *window = game->window;
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);

    if (game->sheriff->bg != NULL)
        sfRenderWindow_drawSprite(window, game->sheriff->bg->sprite, NULL);
    if (game->player->sprite != NULL)
        sfRenderWindow_drawSprite(window, game->player->sprite->sprite, NULL);
    if (game->cat != NULL && game->cat_is_dead == 0)
        sfRenderWindow_drawSprite(window, game->cat->sprite, NULL);
    if (game->sheriff->npc != NULL)
        sfRenderWindow_drawSprite(window, game->sheriff->npc->sprite, NULL);
    draw_dialogue_assets(window, game, center);
}

void destroy_sheriff(sheriff_t *sheriff)
{
    if (sheriff->bg != NULL) {
        destroy_sprite(sheriff->bg);
    }
    if (sheriff->npc != NULL) {
        destroy_sprite(sheriff->npc);
    }
    if (sheriff->dialogue != NULL) {
        destroy_sprite(sheriff->dialogue);
    }
    if (sheriff->icon != NULL) {
        destroy_sprite(sheriff->icon);
    }
    free(sheriff);
}

sheriff_t *create_sheriff(void)
{
    sheriff_t *sheriff = malloc(sizeof(sheriff_t));

    if (sheriff != NULL) {
        sheriff->passed = 0;
        sheriff->bg = create_sprite("./assets/images/sheriff_place.png");
        sheriff->collision = sfImage_createFromFile(
            "./assets/images/sheriff_place_collision.png"
        );
        sheriff->npc = create_sprite("./assets/images/sheriff.png");
        sheriff->dialogue = create_sprite("./assets/images/dialogue.png");
        sheriff->icon = create_sprite("./assets/images/sheriff.png");
        sfSprite_setScale(sheriff->npc->sprite, (sfVector2f){5, 5});
        sfSprite_setScale(sheriff->dialogue->sprite, (sfVector2f){3, 3});
        sfSprite_setScale(sheriff->icon->sprite, (sfVector2f){5, 5});
    }
    return sheriff;
}

void switch_to_sheriff(game_t *game)
{
    game->scene = SCENE_SHERIFF;
    game->sheriff->is_dialogue = 0;
    game->sheriff->text =
        create_dialogue_text("./assets/dialogue/quest2.txt",
            game->player->name);
    set_text_position(game->sheriff->text, (sfVector2f){920, 1012});
    sfSprite_setPosition(game->player->sprite->sprite, (sfVector2f){810, 600});
    sfSprite_setPosition(game->sheriff->npc->sprite, (sfVector2f){920, 445});
    setposition_view(game->window, (sfVector2f){810, 600});
}
