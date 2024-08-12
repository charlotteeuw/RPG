/*
** EPITECH PROJECT, 2023
** myrpg
** File description:
** load.c
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "my.h"

static void set_game_drawer(game_t *game, char **line)
{
    unsigned short quantity = 0;
    enum e_items item = 0;

    if (!strcmp(line[0], "pos")) {
        game->player->pos.x = atof(line[1]);
        game->player->pos.y = atof(line[2]);
    }
    if (!strcmp(line[0], "item") && line[2] != NULL) {
        item = atoi(line[1]);
        if (item > 0 && item < MAX_ITEMS) {
            quantity = atoi(line[2]);
            add_item_to_inventory(game->player->inventory, item, quantity);
        }
    }
}

static void set_quests(game_t *game, char **line)
{
    if (!strcmp(line[0], "quest1"))
        game->player->quests->first_quest = atoi(line[1]);
    if (!strcmp(line[0], "quest2"))
        game->player->quests->second_quest = atoi(line[1]);
    if (!strcmp(line[0], "quest3"))
        game->player->quests->third_quest = atoi(line[1]);
    if (!strcmp(line[0], "quest4"))
        game->player->quests->fourth_quest = atoi(line[1]);
    if (!strcmp(line[0], "quest5"))
        game->player->quests->fifth_quest = atoi(line[1]);
}

static void set_structures(game_t *game, char **line)
{
    if (!strcmp(line[0], "room"))
        game->room->passed = atoi(line[1]);
    if (!strcmp(line[0], "boss"))
        game->boss->passed = atoi(line[1]);
    if (!strcmp(line[0], "sheriff"))
        game->sheriff->passed = atoi(line[1]);
    if (!strcmp(line[0], "shop"))
        game->shop->passed = atoi(line[1]);
    if (!strcmp(line[0], "spawn"))
        game->spawn->passed = atoi(line[1]);
    if (!strcmp(line[0], "outside"))
        game->outside->passed = atoi(line[1]);
    if (!strcmp(line[0], "outside2"))
        game->outside->passed_final = atoi(line[1]);
    if (!strcmp(line[0], "outside3"))
        game->outside->passed_end = atoi(line[1]);
    if (!strcmp(line[0], "outside4"))
        game->outside->passed_night = atoi(line[1]);
    set_quests(game, line);
}

static void set_game(game_t *game, char **line)
{
    if (!strcmp(line[0], "name"))
        game->player->name = my_strdup(line[1]);
    if (!strcmp(line[0], "level"))
        game->player->level = atoi(line[1]);
    if (!strcmp(line[0], "health"))
        game->player->health = atoi(line[1]);
    if (!strcmp(line[0], "experience"))
        game->player->experience = atoi(line[1]);
    if (!strcmp(line[0], "male"))
        game->player->male = atoi(line[1]);
    if (!strcmp(line[0], "scene"))
        game->scene = atoi(line[1]);
    if (!strcmp(line[0], "day"))
        game->is_day = atoi(line[1]);
    if (!strcmp(line[0], "time"))
        game->current_time_in_day = atoi(line[1]);
    if (!strcmp(line[0], "game"))
        game->day = atoi(line[1]);
    set_game_drawer(game, line);
    set_structures(game, line);
}

static void load_game(game_t *game, char *content)
{
    char **lines = my_splitstr(content, "\n");
    char **line = NULL;

    for (size_t i = 0; lines != NULL && lines[i] != NULL; i++) {
        line = my_splitstr(lines[i], ":");
        if (line != NULL && line[0] != NULL && line[1] != NULL) {
            set_game(game, line);
        }
    }
    activate_fade(game->fade);
    spawn_player(game);
}

void resume_game(game_t *game, button_t *button)
{
    const char *filename = sfText_getString(button->text);
    char filepath[200] = {0};
    char *content = NULL;

    if (filename != NULL) {
        snprintf(filepath, 200, "./.backups/%s.save", filename);
        content = my_open(filepath);
        if (content != NULL) {
            load_game(game, content);
        }
    }
}
