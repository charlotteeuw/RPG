/*
** EPITECH PROJECT, 2024
** rpg
** File description:
** tuto.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

void analyse_tuto_events(game_t *game, sfEvent *event)
{
    sfVector2f position = {1000, 940};

    if (game->tuto->dialogue != NULL)
        game->tuto->text = handle_dialogue(game, event, position,
            game->tuto->text);
    if (game->tuto->text == NULL)
        game->scene = SCENE_SPAWN;
}

static void render_tuto_drawer(sfRenderWindow *window, tuto_t *tuto)
{
    if (tuto->dialogue != NULL) {
        sfRenderWindow_drawSprite(window, tuto->dialogue->sprite, NULL);
    }
    if (tuto->icon != NULL) {
        sfRenderWindow_drawSprite(window, tuto->icon->sprite, NULL);
    }
}

void render_tuto(game_t *game)
{
    sfRenderWindow *window = game->window;
    player_t *player = game->player;
    tuto_t *tuto = game->tuto;

    if (window != NULL && player != NULL && tuto != NULL) {
        if (tuto->bg != NULL) {
            sfRenderWindow_drawSprite(window, tuto->bg->sprite, NULL);
        }
        if (player->sprite != NULL) {
            sfRenderWindow_drawSprite(window, player->sprite->sprite, NULL);
        }
        render_tuto_drawer(window, tuto);
        if (tuto->arrow != NULL) {
            sfRenderWindow_drawSprite(window, tuto->arrow->sprite, NULL);
        }
        draw_dialogue(tuto->text, window);
    }
}

void destroy_tuto(tuto_t *tuto)
{
    if (tuto->bg != NULL) {
        destroy_sprite(tuto->bg);
    }
    if (tuto->dialogue != NULL) {
        destroy_sprite(tuto->dialogue);
    }
    if (tuto->icon != NULL) {
        destroy_sprite(tuto->icon);
    }
    free(tuto);
}

tuto_t *create_tuto(void)
{
    tuto_t *tuto = malloc(sizeof(tuto_t));

    if (tuto != NULL) {
        tuto->bg = create_sprite("./assets/images/map_tuto.png");
        tuto->dialogue = create_sprite("./assets/images/dialogue.png");
        tuto->icon = create_sprite("./assets/images/animal_icon.png");
        tuto->arrow = create_sprite("./assets/images/arrow.png");
        sfSprite_setScale(tuto->dialogue->sprite, (sfVector2f){3, 3});
        sfSprite_setPosition(tuto->dialogue->sprite, (sfVector2f){600, 850});
        sfSprite_setScale(tuto->icon->sprite, (sfVector2f){0.7, 0.7});
        sfSprite_setPosition(tuto->icon->sprite, (sfVector2f){642, 892});
        sfSprite_setScale(tuto->arrow->sprite, (sfVector2f){5, 5});
        sfSprite_setPosition(tuto->arrow->sprite, (sfVector2f){500, 500});
    }
    return tuto;
}

void switch_to_tuto(game_t *game)
{
    sfIntRect frame = {0, 0, 0, 0};

    game->scene = SCENE_TUTO;
    game->tuto->text = create_dialogue_text("./assets/dialogue/tuto.txt",
        game->player->name);
    set_text_position(game->tuto->text, (sfVector2f){1000, 960});
    if (game->player->male) {
        frame = (sfIntRect){0, 0, 24, 24};
        game->player->sprite = create_sprite("./assets/images/boy.png");
        sfSprite_setScale(game->player->sprite->sprite, (sfVector2f){5, 5});
    } else {
        frame = (sfIntRect){0, 0, 32, 32};
        game->player->sprite = create_sprite("./assets/images/girl.png");
        sfSprite_setScale(game->player->sprite->sprite, (sfVector2f){6, 6});
    }
    sfSprite_setTextureRect(game->player->sprite->sprite, frame);
    sfSprite_setPosition(game->player->sprite->sprite, (sfVector2f){900, 500});
    center_sprite(game->player->sprite->sprite);
    setposition_view(game->window, (sfVector2f){900, 500});
}
