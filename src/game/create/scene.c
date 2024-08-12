/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** scene.c
*/

#include "my.h"

static void initialiaze_rooms(game_t *game)
{
    game->sheriff = create_sheriff();
    game->spawn = create_spawn();
    game->shop = create_shop();
    game->room = create_room();
    game->boss = create_boss();
}

static void initilialize_ui(game_t *game)
{
    game->selection = create_selection();
    game->settings = create_settings();
    game->resume = create_resume();
    game->title = create_title();
}

static void initialize_outside(game_t *game)
{
    game->outside = create_outside();
    game->tuto = create_tuto();
}

void initialize_scene(game_t *game, enum e_steps step)
{
    switch (step) {
        case INIT_UI:
            initilialize_ui(game);
            break;
        case INIT_OUTSIDE:
            initialize_outside(game);
            break;
        case INIT_ROOMS:
            initialiaze_rooms(game);
            break;
        default:
            break;
    }
}
