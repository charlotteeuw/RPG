/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** main.c
*/

#include <stdlib.h>
#include <string.h>
#include "my_def.h"
#include <stdio.h>
#include "my.h"

static void update_framerate(sfText *text, float fps)
{
    char str[15] = {0};

    if (text != NULL) {
        sprintf(str, "%.0f", fps);
        sfText_setString(text, str);
    }
}

void update_day_night_cycle(game_t *game)
{
    sfTime elapsed_time = sfClock_getElapsedTime(game->clock);
    float total_seconds = sfTime_asSeconds(elapsed_time);
    int current_time_in_day = (int)total_seconds % DAY_PERIOD;
    char str[10] = "Day: \0";

    if (current_time_in_day < DAY_DURATION) {
        game->current_time_in_day = current_time_in_day;
        if (!game->is_day) {
            game->is_day = true;
        }
    } else {
        if (game->is_day) {
            game->is_day = false;
        }
    }
    if (total_seconds / DAY_PERIOD > game->day) {
        game->day++;
    }
    snprintf(str, 10, "Day: %d", game->day);
    sfText_setString(game->day_text, str);
}

static void update_player_stats(game_t *game)
{
    char level[10] = {0};

    snprintf(level, 10, "Level: %d", game->player->level);
    sfText_setString(game->level, level);
}

static void analyse_zombie(game_t *game)
{
    if (!game->is_day) {
        switch (game->scene) {
            case SCENE_OUTSIDE:
                move_zombie(game, game->zombies);
                analyse_zombie_collisions(game);
                break;
            default:
                break;
        }
    }
}

static void manage_game(game_t *game)
{
    update_day_night_cycle(game);
    update_player_stats(game);
    manage_movement(game);
    player_attack(game);
    analyse_zombie(game);
    move_mega(game);
    if (game->fade != NULL && game->fade->active) {
        update_fade(game->fade);
    }
}

static void my_rpg(game_t *game)
{
    sfClock *clock = sfClock_create();
    sfEvent event = {0};
    float delta = 0;

    activate_fade(game->fade);
    while (sfRenderWindow_isOpen(game->window)) {
        while (sfRenderWindow_pollEvent(game->window, &event)) {
            analyse_events(game, &event);
        }
        manage_game(game);
        delta = restart_clock(clock);
        update_rain(game->rain, delta);
        update_snow(game->snow, delta);
        if (delta != 0.0) {
            update_framerate(game->framerate, 1.0 / delta);
        }
        render_game(game);
    }
    sfClock_destroy(clock);
}

static bool manage_arguments(int argc, char **argv, bool *ptr)
{
    char *content = NULL;

    if (argc > 1) {
        if (argc > 2 || strcmp(argv[1], "-h") != 0) {
            my_puts(STDERR_FILENO, "Invalid argument, retry with -h.\n");
        } else {
            content = my_open("./assets/usage");
        }
        if (content != NULL) {
            my_puts(STDOUT_FILENO, content);
            free(content);
            *ptr = true;
        }
        return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    bool success = false;
    game_t game = {0};

    if (manage_arguments(argc, argv, &success)) {
        success = create_game(&game);
        if (success) {
            my_rpg(&game);
        }
        destroy_game(&game);
    }
    return !success;
}
