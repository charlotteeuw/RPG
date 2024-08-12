/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** events_game.c
*/

#include "my.h"
#include <stdio.h>

const sfVector2f teleporters_pos[5] = {
    {.x = 12955.0, .y = 10573.0},
    {.x = 4778.0, .y = 8443.0},
    {.x = 6804.0, .y = 8487.0},
    {.x = 5249.0, .y = 8419.0},
    {.x = 5911.0, .y = 8461.0}
};

void (*teleporters_functions[5])(game_t *game) = {
    switch_to_spawn, switch_to_shop, switch_to_sheriff, switch_to_room,
    switch_to_boss
};

static bool near_teleporter(game_t *game)
{
    float dist = 0.0;

    for (unsigned short i = 0; i < 5; i++) {
        dist = distance_between_coords(game->player->pos, teleporters_pos[i]);
        if (dist > 50.0) {
            continue;
        }
        if (sfKeyboard_isKeyPressed(game->keybinds[BIND_TOOL])) {
            activate_fade(game->fade);
            game->player->pos.x = 0.0;
            game->player->pos.y = 0.0;
            teleporters_functions[i](game);
        } else {
            game->help_displayed = true;
        }
        return true;
    }
    game->help_displayed = false;
    return false;
}

static void dialogue_utils(game_t *game, sfEvent *event)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = {center.x - 100, center.y + 370};

    if (game->outside->dialogue != NULL && game->outside->passed == 0) {
        game->player->moving = 0;
        game->outside->text = handle_dialogue(game, event, pos,
            game->outside->text);
    }
    if (game->outside->dialogue != NULL && game->outside->night == 1) {
        game->outside->night1 = handle_dialogue(game, event, pos,
            game->outside->night1);
    }
    if (game->outside->passed == 0 && game->outside->text == NULL) {
        game->outside->is_dialogue = 0;
        game->outside->passed = 1;
        game->player->moving = 1;
    }
}

static void final_dialogue(game_t *game, sfEvent *event)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = {center.x - 100, center.y + 370};

    if (game->outside->dialogue != NULL) {
        game->outside->final_text = handle_dialogue(game, event, pos,
            game->outside->final_text);
    }
}

static zombie_t **remove_zombie(zombie_t **zombies, size_t i)
{
    while (zombies[i] != NULL) {
        zombies[i] = zombies[i + 1];
        i++;
    }
    return zombies;
}

static void fight_zombies(zombie_t **zombies, game_t *game, sfEvent *event)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player->sprite->sprite);
    sfVector2f zombie_pos;

    if (game->is_day) {
        return;
    }
    if (event->type != sfEvtKeyReleased && event->key.code != sfKeyR)
        return;
    for (size_t i = 0; zombies[i] != NULL; i++) {
        zombie_pos = sfSprite_getPosition(zombies[i]->sprite->sprite);
        if (zombie_pos.x - player_pos.x <= 5 &&
            zombie_pos.y - player_pos.y <= 5) {
            zombies[i]->health -= game->player->damage;
        }
        if (zombies[i]->health <= 0) {
            zombies = remove_zombie(zombies, i);
            game->player->damage += 5;
        }
    }
}

void analyse_game_events(game_t *game, sfEvent *event)
{
    analyse_quests_events(game, event);
    if (!near_teleporter(game)) {
        analyse_zoom_events(game->window, event);
        dialogue_utils(game, event);
        if (game->player->quests->fifth_quest) {
            final_dialogue(game, event);
        }
    }
    analyse_experience(game->player);
    fight_zombies(game->zombies, game, event);
}
