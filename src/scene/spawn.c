/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** spawn.c
*/

#include "my.h"
#include "my_def.h"
#include <stdlib.h>
#include <stdio.h>

spawn_t *create_spawn(void)
{
    spawn_t *spawn = malloc(sizeof(spawn_t));

    if (spawn != NULL) {
        spawn->passed = 0;
        spawn->bedroom = create_sprite("./assets/images/bedroom.png");
        spawn->collision = sfImage_createFromFile(
            "./assets/images/bedroom_collision.png"
        );
        spawn->dialogue = create_sprite("./assets/images/dialogue.png");
        spawn->icon = create_sprite("./assets/images/animal_icon.png");
        sfSprite_setScale(spawn->dialogue->sprite, (sfVector2f){3, 3});
        sfSprite_setScale(spawn->icon->sprite, (sfVector2f){0.7, 0.7});
    }
    return spawn;
}

void destroy_spawn(spawn_t *spawn)
{
    if (spawn->bedroom != NULL) {
        destroy_sprite(spawn->bedroom);
    }
    free(spawn);
}

static void analyse_interaction(game_t *game, sfEvent *event, int *interaction)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = {center.x - 100, center.y + 370};
    static int do_once = 1;

    if (game->spawn->passed == 1)
        return;
    game->spawn->is_dialogue = 1;
    if (game->spawn->dialogue != NULL) {
        game->spawn->text =
            handle_dialogue(game, event, pos, game->spawn->text);
    }
    if (game->spawn->text == NULL && do_once == 1) {
        game->spawn->passed = 1;
        *interaction = 0;
        game->spawn->is_dialogue = 0;
        do_once = 0;
        game->cat_is_dead = 1;
        game->player->quests->fourth_quest = 1;
    }
}

static void draw_dialogue_assets2(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->spawn->icon != NULL && game->spawn->is_dialogue == 1
        && game->day == 3) {
        sfSprite_setPosition(game->spawn->icon->sprite,
            (sfVector2f){bottom.x + 40, bottom.y + 50});
        sfRenderWindow_drawSprite(window, game->spawn->icon->sprite, NULL);
    }
    if (game->spawn->is_dialogue == 1 && game->day == 3) {
        draw_dialogue(game->spawn->text, window);
    }
}

static void draw_dialogue_assets(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->spawn->passed == 1)
        return;
    if (game->spawn->dialogue != NULL && game->spawn->is_dialogue == 1
        && game->day == 3) {
        sfSprite_setPosition(game->spawn->dialogue->sprite, bottom);
        sfRenderWindow_drawSprite(window, game->spawn->dialogue->sprite,
            NULL);
    }
    draw_dialogue_assets2(window, game, center);
}

void render_spawn(game_t *game)
{
    sfRenderWindow *window = game->window;
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);
    player_t *player = game->player;
    spawn_t *spawn = game->spawn;

    if (window != NULL && player != NULL && spawn != NULL) {
        if (spawn->bedroom != NULL) {
            sfRenderWindow_drawSprite(window, spawn->bedroom->sprite, NULL);
        }
        if (player->sprite != NULL) {
            sfRenderWindow_drawSprite(window, player->sprite->sprite, NULL);
        }
        draw_dialogue_assets(window, game, center);
    }
}

void analyse_spawn_events(game_t *game, __attribute__((unused)) sfEvent *event)
{
    sfVector2f position = sfSprite_getPosition(game->player->sprite->sprite);
    static int interaction = 1;

    if (position.y >= 1080) {
        start_game(game, (sfVector2f){12950, 10600});
    }
    if (interaction == 1 && game->day == 3) {
        analyse_interaction(game, event, &interaction);
    }
}

void switch_to_spawn(game_t *game)
{
    game->scene = SCENE_SPAWN;
    game->player->pos = (sfVector2f){850, 600};
    spawn_player(game);
    game->spawn->text = create_dialogue_text("./assets/dialogue/hurt_cat.txt",
        game->player->name);
}
