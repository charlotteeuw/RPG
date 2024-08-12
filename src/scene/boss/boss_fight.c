/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** boss_fight.c
*/

#include <my.h>
#include <my_def.h>
#include <math.h>

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

static void mega_zombie_move(game_t *game, zombie_t *mega, sfTime time)
{
    sfVector2f player_pos = sfSprite_getPosition(game->player->sprite->sprite);
    sfVector2f move;
    float norm;

    mega->pos = sfSprite_getPosition(mega->sprite->sprite);
    mega->bounds = sfSprite_getGlobalBounds(mega->sprite->sprite);
    move.x = player_pos.x - mega->pos.x;
    move.y = player_pos.y - mega->pos.y;
    norm = sqrt(move.x * move.x + move.y * move.y);
    move.x /= norm;
    move.y /= norm;
    update_zombie_position(mega, move);
    mega->position.x += move.x * time.microseconds / 100000 * 4;
    mega->position.y += move.y * time.microseconds / 100000 * 4;
    sfSprite_setPosition(mega->sprite->sprite, mega->position);
}

void move_mega(game_t *game)
{
    static sfClock *clock = NULL;
    sfTime time;

    if (game->scene != SCENE_BOSS) {
        return;
    }
    if (clock == NULL)
        clock = sfClock_create();
    time = sfClock_getElapsedTime(clock);
    sfClock_restart(clock);
    mega_zombie_move(game, game->boss->mega, time);
}

zombie_t *create_mega(void)
{
    zombie_t *mega = create_zombie();

    mega->health = 500;
    sfSprite_setScale(mega->sprite->sprite, (sfVector2f){10, 10});
    mega->position = (sfVector2f){956, 283};
    sfSprite_setPosition(mega->sprite->sprite, (sfVector2f){956, 283});
    return mega;
}
