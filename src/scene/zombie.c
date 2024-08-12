/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** zombie.c
*/

#include "my_def.h"
#include "my.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

const sfVector2f zombie_pos[10] = {
    {.x = 4657, .y = 9232},
    {.x = 5246, .y = 8970},
    {.x = 6477, .y = 8928},
    {.x = 7186, .y = 9335},
    {.x = 7712, .y = 8905},
    {.x = 8685, .y = 8057},
    {.x = 7497, .y = 7745},
    {.x = 6009, .y = 9390},
    {.x = 3818, .y = 8084},
    {.x = 3003, .y = 8411}
};

static void animate_zombie(zombie_t *zombie, sfVector2f move, sfIntRect *frame)
{
    static sfClock *clock;
    sfTime elapsed_time;

    if (!clock) {
        clock = sfClock_create();
    }
    elapsed_time = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(elapsed_time) > ANIMATION_DURATION) {
        frame->left += 32;
        if (frame->left >= 32 * 8)
            frame->left = 0;
        sfClock_restart(clock);
    }
    sfSprite_setTextureRect(zombie->sprite->sprite, *frame);
    sfSprite_move(zombie->sprite->sprite, move);
}

static void update_zombie_position(zombie_t *zombie, sfVector2f move)
{
    static sfIntRect frame = {0, 0, 32, 32};

    if (move.x > 0) {
        frame.top = 32 * 2;
    }
    if (move.x < 0) {
        frame.top = 32 * 3;
    }
    if (move.y < 0) {
        frame.top = 32;
    }
    if (move.y > 0) {
        frame.top = 0;
    }
    animate_zombie(zombie, move, &frame);
}

static void calculate_move(game_t *game, zombie_t **zombies, sfTime time)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player->sprite->sprite);
    sfVector2f move;
    float norm;

    for (size_t i = 0; zombies[i] != NULL; i++) {
        zombies[i]->pos = sfSprite_getPosition(zombies[i]->sprite->sprite);
        zombies[i]->bounds =
            sfSprite_getGlobalBounds(game->zombies[i]->sprite->sprite);
        move.x = player_pos.x - zombies[i]->pos.x;
        move.y = player_pos.y - zombies[i]->pos.y;
        norm = sqrt(move.x * move.x + move.y * move.y);
        move.x /= norm;
        move.y /= norm;
        update_zombie_position(zombies[i], move);
        zombies[i]->position.x += move.x * time.microseconds / 100000 * 3;
        zombies[i]->position.y += move.y * time.microseconds / 100000 * 3;
        sfSprite_setPosition(zombies[i]->sprite->sprite, zombies[i]->position);
    }
}

void analyse_zombie_collisions(game_t *game)
{
    sfFloatRect player_bounds =
        sfSprite_getGlobalBounds(game->player->sprite->sprite);

    for (size_t i = 0; game->zombies[i] != NULL; i++) {
        if (sfFloatRect_intersects(&game->zombies[i]->bounds,
            &player_bounds, NULL) &&
            game->zombies[i]->last + 2 <
                sfTime_asSeconds(sfClock_getElapsedTime(game->clock))) {
            game->zombies[i]->last =
                sfTime_asSeconds(sfClock_getElapsedTime(game->clock));
            game->player->health -= 10;
        }
    }
}

void move_zombie(game_t *game, zombie_t **zombies)
{
    static sfClock *clock = NULL;
    sfTime time;

    if (clock == NULL)
        clock = sfClock_create();
    time = sfClock_getElapsedTime(clock);
    sfClock_restart(clock);
    calculate_move(game, zombies, time);
}

zombie_t *create_zombie(void)
{
    zombie_t *zombie = malloc(sizeof(zombie_t));

    if (zombie != NULL) {
        zombie->sprite = create_sprite("./assets/images/zombie.png");
        zombie->frame = (sfIntRect){0, 0, 32, 32};
        zombie->position = zombie_pos[rand() % 10];
        zombie->health = 100;
        sfSprite_setTextureRect(zombie->sprite->sprite, zombie->frame);
        sfSprite_setScale(zombie->sprite->sprite, (sfVector2f){5, 5});
        sfSprite_setPosition(zombie->sprite->sprite, zombie->position);
    }
    return zombie;
}
