/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** boss.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

boss_t *create_boss(void)
{
    boss_t *boss = malloc(sizeof(boss_t));

    if (boss != NULL) {
        boss->fight = 0;
        boss->passed = 0;
        boss->mega = create_mega();
        boss->bg = create_sprite("./assets/images/boss_room.png");
        boss->collision = sfImage_createFromFile(
            "./assets/images/boss_room_collision.png"
        );
        boss->dialogue = create_sprite("./assets/images/dialogue.png");
        boss->icon = create_sprite("./assets/images/zombie_icon.png");
        sfSprite_setScale(boss->dialogue->sprite, (sfVector2f){3, 3});
        sfSprite_setScale(boss->icon->sprite, (sfVector2f){0.1, 0.1});
    }
    return boss;
}

void destroy_boss(boss_t *boss)
{
    if (boss->bg != NULL) {
        destroy_sprite(boss->bg);
    }
    free(boss);
}

static void draw_dialogue_assets2(game_t *game, sfVector2f center,
    int dialogue, int *do_once)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->boss->icon != NULL && game->boss->is_dialogue == 1
        && dialogue == 1 && *do_once == 1) {
        sfSprite_setPosition(game->boss->icon->sprite,
            (sfVector2f){bottom.x + 40, bottom.y + 50});
        sfRenderWindow_drawSprite(game->window, game->boss->icon->sprite,
            NULL);
    }
    if (game->boss->is_dialogue == 1 && dialogue == 1) {
        draw_dialogue(game->boss->text, game->window);
    }
    if (game->boss->text == NULL)
        *do_once = 0;
}

static void draw_dialogue_assets(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};
    static int dialogue = 1;
    static int do_once = 1;

    if (game->boss->passed == 1)
        return;
    if (!game->boss->is_dialogue)
        dialogue = 0;
    else
        dialogue = 1;
    if (game->boss->dialogue != NULL && game->boss->is_dialogue == 1
        && dialogue == 1 && do_once == 1) {
        sfSprite_setPosition(game->boss->dialogue->sprite, bottom);
        sfRenderWindow_drawSprite(window, game->boss->dialogue->sprite,
            NULL);
    }
    draw_dialogue_assets2(game, center, dialogue, &do_once);
}

void render_boss(game_t *game)
{
    sfRenderWindow *window = game->window;
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);
    player_t *player = game->player;
    boss_t *boss = game->boss;

    if (window != NULL && player != NULL && boss != NULL) {
        if (boss->bg != NULL) {
            sfRenderWindow_drawSprite(window, boss->bg->sprite, NULL);
        }
        if (game->player->sprite != NULL)
            sfRenderWindow_drawSprite(window, player->sprite->sprite, NULL);
        if (boss->mega != NULL) {
            sfRenderWindow_drawSprite(
                window, boss->mega->sprite->sprite, NULL
            );
        }
    }
    draw_dialogue_assets(window, game, center);
}

static void analyse_interaction(game_t *game, sfEvent *event)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f bottom = {center.x - 70, center.y + 380};
    static int do_once = 1;

    if (game->boss->passed == 1)
        return;
    game->boss->is_dialogue = 1;
    if (game->boss->dialogue != NULL)
        game->boss->text =
        handle_dialogue(game, event, bottom, game->boss->text);
    if (game->boss->text == NULL && do_once == 1) {
        game->boss->passed = 1;
        game->boss->is_dialogue = 0;
        game->boss->fight = 0;
        game->player->experience += 100;
        game->player->quests->fifth_quest = 1;
        game->cat_is_dead = 0;
        do_once = 0;
    }
}

void analyse_boss_events(game_t *game, __attribute__((unused)) sfEvent *event)
{
    sfVector2f position = sfSprite_getPosition(game->player->sprite->sprite);

    if (position.y >= 1382) {
        start_game(game, (sfVector2f){5911, 8461});
    }
    game->boss->fight = 1;
    if (game->boss->fight == 1) {
        analyse_interaction(game, event);
    }
}

void switch_to_boss(game_t *game)
{
    if (!game->player->quests->third_quest)
        return;
    game->scene = SCENE_BOSS;
    game->boss->text = create_dialogue_text("./assets/dialogue/final.txt",
        game->player->name);
    sfSprite_setPosition(game->player->sprite->sprite, (sfVector2f){810, 600});
    setposition_view(game->window, (sfVector2f){810, 600});
}
