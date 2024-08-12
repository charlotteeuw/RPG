/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** animate_player.c
*/

#include <my.h>
#include <my_def.h>

void attack_animation(player_t *player, sfIntRect *frame)
{
    static sfClock *clock = NULL;
    sfVector2u texture_size = sfTexture_getSize(player->attack->texture);
    sfTime time = sfTime_Zero;

    if (clock == NULL) {
        clock = sfClock_create();
    }
    time = sfClock_getElapsedTime(clock);
    if (sfTime_asSeconds(time) > ATTACK_ANIMATION_DURATION) {
        frame->left += frame->width;
        if ((unsigned int)frame->left >= texture_size.x) {
            player->attacking = false;
        }
        sfClock_restart(clock);
    }
    if (player->attacking) {
        sfSprite_setTextureRect(player->attack->sprite, *frame);
        sfSprite_setPosition(player->attack->sprite, player->pos);
    }
}

void player_attack(game_t *game)
{
    static sfIntRect frame = {0};

    if (game->player != NULL && game->player->attack != NULL &&
        game->player->attack->sprite != NULL && game->player->sprite != NULL &&
        game->player->attack->texture != NULL &&
        game->player->sprite->sprite != NULL) {
        if (!game->player->attacking && sfKeyboard_isKeyPressed(sfKeyR)) {
            game->player->attacking = true;
            frame = sfSprite_getTextureRect(game->player->sprite->sprite);
            frame.left = 0;
        }
        if (game->player->attacking) {
            attack_animation(game->player, &frame);
        }
    }
}
