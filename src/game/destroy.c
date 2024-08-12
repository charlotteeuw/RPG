/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** destroy.c
*/

#include <stdlib.h>
#include "my.h"

static void destroy_sounds(sound_t *sounds[MAX_SOUNDS])
{
    for (size_t i = 0; i < MAX_SOUNDS; i++) {
        if (sounds[i] != NULL) {
            destroy_sound(sounds[i]);
        }
    }
}

static void destroy_scenes_drawer(game_t *game)
{
    if (game->shop != NULL) {
        destroy_shop(game->shop);
    }
    if (game->resume != NULL) {
        destroy_resume(game->resume);
    }
    if (game->boss != NULL) {
        destroy_boss(game->boss);
    }
}

static void destroy_scenes(game_t *game)
{
    if (game->title != NULL) {
        destroy_title(game->title);
    }
    if (game->settings != NULL) {
        destroy_settings(game->settings);
    }
    if (game->selection != NULL) {
        destroy_selection(game->selection);
    }
    if (game->tuto != NULL) {
        destroy_tuto(game->tuto);
    }
    if (game->outside != NULL) {
        destroy_outside(game->outside);
    }
    if (game->sheriff != NULL) {
        destroy_sheriff(game->sheriff);
    }
    destroy_scenes_drawer(game);
}

static void destroy_player(player_t *player)
{
    if (player->sprite != NULL) {
        destroy_sprite(player->sprite);
    }
    if (player->clock != NULL) {
        sfClock_destroy(player->clock);
    }
    if (player->name != NULL) {
        free(player->name);
    }
    if (player->inventory != NULL) {
        destroy_inventory(player->inventory);
    }
    if (player->pause) {
        destroy_pause(player->pause);
    }
    if (player->quests != NULL) {
        destroy_quests(player->quests);
    }
    free(player);
}

static void destroy_game_components(game_t *game)
{
    if (game->window != NULL) {
        sfRenderWindow_destroy(game->window);
    }
    destroy_sprite(game->bg);
    destroy_sprite(game->cursor);
    destroy_sprite(game->cat);
    if (game->framerate != NULL) {
        sfText_destroy(game->framerate);
    }
    if (game->player != NULL) {
        destroy_player(game->player);
    }
    if (game->keybinds != NULL) {
        free(game->keybinds);
    }
    destroy_fade(game->fade);
}

void destroy_game(game_t *game)
{
    destroy_game_components(game);
    destroy_sounds(game->sounds);
    destroy_scenes(game);
}
