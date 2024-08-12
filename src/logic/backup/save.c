/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** save.c
*/

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "my.h"

const char *backup_dir = "./.backups";

static void save_player(player_t *player, int fd)
{
    if (player->name != NULL) {
        dprintf(fd, "name:%s\n", player->name);
    }
    dprintf(fd, "level:%d\n", player->level);
    dprintf(fd, "health:%d\n", player->health);
    dprintf(fd, "expereince:%d\n", player->experience);
    dprintf(fd, "pos:%f:%f\n", player->pos.x, player->pos.y);
    for (enum e_items i = 0; player->inventory != NULL && i < MAX_ITEMS; i++) {
        dprintf(fd, "item:%d:%d\n", i, player->inventory->items[i]->quantity);
    }
    dprintf(fd, "male:%d\n", player->male);
}

static void save_quests(quests_t *quests, int fd)
{
    dprintf(fd, "quest1:%d\n", quests->first_quest);
    dprintf(fd, "quest2:%d\n", quests->second_quest);
    dprintf(fd, "quest3:%d\n", quests->third_quest);
    dprintf(fd, "quest4:%d\n", quests->fourth_quest);
    dprintf(fd, "quest5:%d\n", quests->fifth_quest);
}

static void save_to_file(game_t *game, int fd)
{
    if (game->player != NULL) {
        save_player(game->player, fd);
        save_quests(game->player->quests, fd);
    }
    dprintf(fd, "game:%d\n", game->day);
    dprintf(fd, "scene:%d\n", game->scene);
    dprintf(fd, "day:%d\n", game->is_day);
    dprintf(fd, "time:%d\n", game->current_time_in_day);
    dprintf(fd, "room:%d\n", game->room->passed);
    dprintf(fd, "boss:%d\n", game->boss->passed);
    dprintf(fd, "sheriff:%d\n", game->sheriff->passed);
    dprintf(fd, "shop:%d\n", game->shop->passed);
    dprintf(fd, "spawn:%d\n", game->spawn->passed);
    dprintf(fd, "outside:%d\n", game->outside->passed);
    dprintf(fd, "outside2:%d\n", game->outside->passed_final);
    dprintf(fd, "outside3:%d\n", game->outside->passed_end);
    dprintf(fd, "outside4:%d\n", game->outside->passed_night);
}

void save_game(game_t *game, __attribute__((unused)) button_t *button)
{
    char *date = create_date();
    struct stat st = {0};
    char str[50] = {0};
    int fd = 0;

    if (stat(backup_dir, &st) != 0) {
        my_puts(STDOUT_FILENO, "Creating backup directory...\n");
        mkdir(backup_dir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    if (date != NULL) {
        snprintf(str, 50, "%s/%s.save", backup_dir, date);
        fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
        if (fd != -1) {
            save_to_file(game, fd);
            close(fd);
        } else {
            my_puts(STDOUT_FILENO, "Error while saving the game\n");
        }
        free(date);
    }
}
