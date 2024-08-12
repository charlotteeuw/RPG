/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** collision.c
*/

#include <my.h>
#include <math.h>

static sfFloatRect entity_bounds(sfSprite *sprite)
{
    sfFloatRect hitbox = sfSprite_getGlobalBounds(sprite);

    hitbox.height = hitbox.height / 2;
    hitbox.top = hitbox.top + hitbox.height;
    return hitbox;
}

static void horizontal_collision(sfSprite *sprite,
    sfImage *map, sfVector2f *move)
{
    sfVector2f mid = sfSprite_getPosition(sprite);
    sfFloatRect bounds = entity_bounds(sprite);
    sfVector2u size = sfImage_getSize(map);
    sfColor color = {0};
    float bounds_right = bounds.left + bounds.width;

    if (0 < bounds.left && bounds.left < size.x &&
        0 < mid.y && mid.y < size.y) {
        color = sfImage_getPixel(map, bounds.left, mid.y);
        if (color.r == 255 && move->x < 0) {
            move->x = 0;
        }
    }
    if (0 < bounds_right && bounds_right < size.x &&
        0 < mid.y && mid.y < size.y) {
        color = sfImage_getPixel(map, bounds_right, mid.y);
        if (color.r == 255 && move->x > 0) {
            move->x = 0;
        }
    }
}

static void vertical_collision(sfSprite *sprite,
    sfImage *map, sfVector2f *move)
{
    sfVector2f mid = sfSprite_getPosition(sprite);
    sfFloatRect bounds = entity_bounds(sprite);
    sfVector2u size = sfImage_getSize(map);
    sfColor color = {0};
    float bounds_down = bounds.top + bounds.height;

    if (0 < bounds.top && bounds.top < size.y &&
        0 < mid.x && mid.x < size.x) {
        color = sfImage_getPixel(map, mid.x, bounds.top);
        if (color.r == 255 && move->y < 0) {
            move->y = 0;
        }
    }
    if (0 < bounds_down && bounds_down < size.y &&
        0 < mid.x && mid.x < size.x) {
        color = sfImage_getPixel(map, mid.x, bounds_down);
        if (color.r == 255 && move->y > 0) {
            move->y = 0;
        }
    }
}

static void map_collision(sfSprite *sprite, sfImage *map, sfVector2f *move)
{
    horizontal_collision(sprite, map, move);
    vertical_collision(sprite, map, move);
}

static void entity_collison(sfVector2f p_pos, sfFloatRect p_bounds,
    sfSprite *e_sprite, sfVector2f *move)
{
    sfVector2f e_pos = sfSprite_getPosition(e_sprite);
    sfFloatRect e_bounds = entity_bounds(e_sprite);
    sfFloatRect intersection = {0};
    sfVector2f dir = {0};

    dir = (sfVector2f){p_pos.x - e_pos.x, p_pos.y - e_pos.y};
    dir = (sfVector2f){dir.x / fabs(dir.x), dir.y / fabs(dir.y)};
    if (!sfFloatRect_intersects(&p_bounds, &e_bounds, &intersection)) {
        return;
    }
    if (intersection.width < intersection.height) {
        move->x = dir.x * intersection.width;
    } else {
        move->y = dir.y * intersection.height;
    }
}

static void npc_collision(player_t *player, npc_t **npcs, sfVector2f *move)
{
    sfFloatRect p_bounds = entity_bounds(player->sprite->sprite);
    sfVector2f p_pos = sfSprite_getPosition(player->sprite->sprite);

    for (size_t i = 0; npcs[i] != NULL; i++) {
        entity_collison(p_pos, p_bounds, npcs[i]->sprite->sprite, move);
    }
}

static void z_collision(game_t *game, zombie_t **zombies, sfVector2f *move)
{
    sfSprite *p_sprite = game->player->sprite->sprite;
    sfFloatRect p_bounds = entity_bounds(p_sprite);
    sfVector2f p_pos = sfSprite_getPosition(p_sprite);

    if (game->is_day) {
        return;
    }
    for (size_t i = 0; zombies[i] != NULL; i++) {
        entity_collison(p_pos, p_bounds, zombies[i]->sprite->sprite, move);
    }
}

static sfImage *get_collision_map(game_t *game)
{
    switch (game->scene) {
        case SCENE_OUTSIDE:
            return game->outside->collision;
        case SCENE_ROOM:
            return game->room->collision;
        case SCENE_SHERIFF:
            return game->sheriff->collision;
        case SCENE_SHOP:
            return game->shop->collision;
        case SCENE_BOSS:
            return game->boss->collision;
        case SCENE_SPAWN:
            return game->spawn->collision;
        default:
            return NULL;
    }
}

void analyse_collision(game_t *game, sfVector2f *move)
{
    sfImage *collision_map = get_collision_map(game);

    if (collision_map != NULL) {
        map_collision(game->player->sprite->sprite, collision_map, move);
    }
    npc_collision(game->player, game->npcs, move);
    z_collision(game, game->zombies, move);
}
