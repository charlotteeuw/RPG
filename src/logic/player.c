/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** player.c
*/

#include "my.h"

static void create_male(player_t *player)
{
    sfIntRect rect = {0, 0, 24, 24};
    sfVector2f scale = {5.0, 5.0};

    player->sprite = create_sprite("./assets/images/boy.png");
    player->attack = create_sprite("./assets/images/man_animation.png");
    if (player->sprite != NULL) {
        sfSprite_setTextureRect(player->sprite->sprite, rect);
        sfSprite_setScale(player->sprite->sprite, scale);
        center_sprite(player->sprite->sprite);
    }
    if (player->attack != NULL) {
        sfSprite_setTextureRect(player->attack->sprite, rect);
        sfSprite_setScale(player->attack->sprite, scale);
        center_sprite(player->attack->sprite);
    }
}

static void create_female(player_t *player)
{
    sfIntRect rect = {0, 0, 32, 32};
    sfVector2f scale = {6.0, 6.0};

    player->sprite = create_sprite("./assets/images/girl.png");
    player->attack = create_sprite("./assets/images/attack_girl.png");
    if (player->sprite != NULL) {
        sfSprite_setTextureRect(player->sprite->sprite, rect);
        sfSprite_setScale(player->sprite->sprite, scale);
        center_sprite(player->sprite->sprite);
    }
    if (player->attack != NULL) {
        sfSprite_setTextureRect(player->attack->sprite, rect);
        sfSprite_setScale(player->attack->sprite, scale);
        center_sprite(player->attack->sprite);
    }
}

void reset_menu_state(player_t *player)
{
    if (player != NULL && player->inventory != NULL) {
        player->inventory->is_open = false;
    }
    if (player != NULL && player->quests != NULL) {
        player->quests->is_open = false;
    }
    if (player != NULL && player->pause != NULL) {
        player->pause->is_open = false;
    }
    player->moving = true;
}

void spawn_player(game_t *game)
{
    if (game->player->male) {
        create_male(game->player);
    } else {
        create_female(game->player);
    }
    reset_menu_state(game->player);
    if (game->player->sprite != NULL) {
        sfSprite_setPosition(game->player->sprite->sprite, game->player->pos);
    }
    if (game->window != NULL) {
        setposition_view(game->window, game->player->pos);
    }
}
