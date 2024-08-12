/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** render_quests.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"
#include <stdio.h>

static void render_boss_quest(sfRenderWindow *window, quests_t *quests,
    int day)
{
    sfVector2f pos = {0.485, 0.36};

    if (day >= 4) {
        pos = (sfVector2f){0.485, 0.31};
        sfText_setPosition(quests->quest5, (sfVector2f){0.285, 0.3});
    }
    if (quests->fifth_quest == 1) {
        sfSprite_setPosition(quests->checked->sprite, pos);
        view_dynamic_drawsprite(window, quests->checked->sprite);
    } else {
        sfSprite_setPosition(quests->unchecked->sprite, pos);
        view_dynamic_drawsprite(window, quests->unchecked->sprite);
    }
}

static void render_third_day(sfRenderWindow *window, quests_t *quests)
{
    sfVector2f pos = {0.485, 0.31};

    if (quests->fourth_quest == 1) {
        sfSprite_setPosition(quests->checked->sprite, pos);
        view_dynamic_drawsprite(window, quests->checked->sprite);
    } else {
        sfSprite_setPosition(quests->unchecked->sprite, pos);
        view_dynamic_drawsprite(window, quests->unchecked->sprite);
    }
}

static void render_second_day(sfRenderWindow *window, quests_t *quests)
{
    sfVector2f first = {0.485, 0.31};
    sfVector2f second = {0.485, 0.36};

    if (quests->second_quest == 1) {
        sfSprite_setPosition(quests->checked->sprite, first);
        view_dynamic_drawsprite(window, quests->checked->sprite);
    } else {
        sfSprite_setPosition(quests->unchecked->sprite, first);
        view_dynamic_drawsprite(window, quests->unchecked->sprite);
    }
    if (quests->third_quest == 1) {
        sfSprite_setPosition(quests->checked->sprite, second);
        view_dynamic_drawsprite(window, quests->checked->sprite);
    } else {
        sfSprite_setPosition(quests->unchecked->sprite, second);
        view_dynamic_drawsprite(window, quests->unchecked->sprite);
    }
}

static void render_first_day(sfRenderWindow *window, quests_t *quests)
{
    if (quests->first_quest == 1)
        view_dynamic_drawsprite(window, quests->checked->sprite);
    else
        view_dynamic_drawsprite(window, quests->unchecked->sprite);
}

static void draw_stats(sfRenderWindow *window, quests_t *quests)
{
    sfText_setPosition(quests->xp, (sfVector2f){0.6, 0.3});
    sfText_setPosition(quests->lvl, (sfVector2f){0.575, 0.35});
    sfText_setPosition(quests->health, (sfVector2f){0.575, 0.4});
    sfText_setPosition(quests->dmg, (sfVector2f){0.585, 0.45});
    sfText_setPosition(quests->spd, (sfVector2f){0.575, 0.5});
    view_dynamic_drawtext(window, quests->stats);
    view_dynamic_drawtext(window, quests->level);
    view_dynamic_drawtext(window, quests->experience);
    view_dynamic_drawtext(window, quests->xp);
    view_dynamic_drawtext(window, quests->lvl);
    view_dynamic_drawtext(window, quests->life);
    view_dynamic_drawtext(window, quests->damage);
    view_dynamic_drawtext(window, quests->speed);
    view_dynamic_drawtext(window, quests->health);
    view_dynamic_drawtext(window, quests->dmg);
    view_dynamic_drawtext(window, quests->spd);
}

static void create_stats(sfRenderWindow *window, quests_t *quests,
    game_t *game)
{
    char *experience = my_itoa(game->player->experience);
    char *level = my_itoa(game->player->level);
    char *health = my_itoa(game->player->health);
    char *dmg = my_itoa(game->player->damage);
    char *spd = my_itoa(quests->fast);

    quests->xp = create_text(experience, C_DARK_TEXT, 20);
    quests->lvl = create_text(level, C_DARK_TEXT, 20);
    quests->health = create_text(health, C_DARK_TEXT, 20);
    quests->dmg = create_text(dmg, C_DARK_TEXT, 20);
    quests->spd = create_text(spd, C_DARK_TEXT, 20);
    draw_stats(window, quests);
}

static void render_days(sfRenderWindow *window, quests_t *quests, game_t *game)
{
    if (quests->first_quest == 0) {
        view_dynamic_drawtext(window, quests->quest1);
        render_first_day(window, quests);
    }
    if (game->day >= 2 && quests->first_quest == 1) {
        view_dynamic_drawtext(window, quests->quest2);
        view_dynamic_drawtext(window, quests->quest3);
        render_second_day(window, quests);
    }
    if (game->day >= 3 && quests->first_quest && quests->second_quest &&
        quests->third_quest) {
        view_dynamic_drawtext(window, quests->quest4);
        render_third_day(window, quests);
    }
    if (game->day >= 4 && quests->first_quest && quests->second_quest &&
        quests->third_quest && quests->fourth_quest) {
        view_dynamic_drawtext(window, quests->quest5);
        render_boss_quest(window, quests, game->day);
    }
}

void render_quests(sfRenderWindow *window, quests_t *quests, game_t *game)
{
    if (quests != NULL && quests->is_open) {
        view_dynamic_drawsprite(window, quests->img->sprite);
        view_dynamic_drawtext(window, quests->quests);
        create_stats(window, quests, game);
        render_days(window, quests, game);
    }
}
