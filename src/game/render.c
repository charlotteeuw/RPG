/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** render.c
*/

#include "my_def.h"
#include "my.h"

void (*render_functions[MAX_SCENES])(game_t *) = {
    render_title, render_settings, render_selection, render_tuto, render_spawn,
    render_outside, render_shop, render_sheriff, render_room, render_boss,
    render_resume
};

static void render_minimap(game_t *game)
{
    sfView *world_view = sfView_copy(sfRenderWindow_getView(game->window));
    sfView *minimap_view = NULL;

    switch (game->scene) {
        case SCENE_OUTSIDE:
            minimap_view =
                sfView_createFromRect((sfFloatRect){0, 0, 3840 * 5, 2560 * 5});
            sfView_setViewport(minimap_view,
                (sfFloatRect){0.75f, 0.f, 0.25f, 0.25f});
            sfRenderWindow_setView(game->window, minimap_view);
            render_outside(game);
        default:
            break;
    }
    sfRenderWindow_setView(game->window, world_view);
    sfView_destroy(minimap_view);
    sfView_destroy(world_view);
}

static void redirect_to_scene(game_t *game)
{
    for (size_t i = 0; i < MAX_SCENES; i++) {
        if (game->scene == i) {
            render_functions[i](game);
            return;
        }
    }
}

static void draw_zombies(game_t *game)
{
    if (game->zombies != NULL) {
        for (size_t i = 0; game->zombies[i] != NULL; i++) {
            sfRenderWindow_drawSprite(game->window,
                game->zombies[i]->sprite->sprite, NULL);
        }
    }
}

static sfIntRect update_frame(int health)
{
    sfIntRect rect = {0, 0, 350, 118};

    if (health >= 80 && health <= 100) {
        rect.top = 0;
    }
    if (health >= 60 && health < 80) {
        rect.top = 118;
    }
    if (health >= 40 && health < 60) {
        rect.top = 118 * 2;
    }
    if (health >= 20 && health < 40) {
        rect.top = 118 * 3;
    }
    if (health >= 1 && health < 20) {
        rect.top = 118 * 4;
    }
    return rect;
}

static void render_health_bar(game_t *game)
{
    sfIntRect rect = update_frame(game->player->health);

    if (game->player->health <= 0) {
        game->player->health = 100;
        switch_to_spawn(game);
        rect.top = 100;
    }
    sfSprite_setTextureRect(game->player->health_bar->sprite, rect);
    view_dynamic_drawsprite(game->window, game->player->health_bar->sprite);
}

static void render_game_components(game_t *game)
{
    render_npcs(game->window, game->npcs);
    render_quests(game->window, game->player->quests, game);
    if (!game->is_day) {
        draw_zombies(game);
    }
    if (game->day_text != NULL) {
        view_dynamic_drawtext(game->window, game->day_text);
    }
    if (game->level != NULL) {
        view_dynamic_drawtext(game->window, game->level);
    }
    if (game->player != NULL && game->player->health_bar != NULL) {
        render_health_bar(game);
    }
    if (game->player != NULL && game->player->inventory != NULL) {
        render_inventory(game->window, game->player->inventory);
    }
    if (game->player != NULL && game->player->pause != NULL) {
        render_pause(game->window, game->player->pause);
    }
}

void draw_rain(sfRenderWindow *window, rain_t *particles)
{
    for (size_t i = 0; i < 1000; i++) {
        view_drawsprite(window, particles[i].sprite->sprite);
    }
}

void draw_snow(sfRenderWindow *window, snow_t *particles)
{
    for (size_t i = 0; i < 500; i++) {
        view_drawsprite(window, particles[i].sprite->sprite);
    }
}

void render_game(game_t *game)
{
    sfRenderWindow_clear(game->window, sfBlack);
    redirect_to_scene(game);
    if (is_game_scene(game->scene)) {
        render_game_components(game);
    }
    render_minimap(game);
    if (game->fade != NULL && game->fade->active && game->fade->img != NULL) {
        sfRenderWindow_drawRectangleShape(game->window, game->fade->img, NULL);
    }
    if (game->framerate != NULL && game->framerate_displayed) {
        view_dynamic_drawtext(game->window, game->framerate);
    }
    if (game->cursor != NULL && game->cursor->sprite != NULL) {
        view_drawsprite(game->window, game->cursor->sprite);
    }
    if (game->help_displayed && game->help != NULL) {
        view_dynamic_drawtext(game->window, game->help);
    }
    sfRenderWindow_display(game->window);
}

void render_player(sfRenderWindow *window, player_t *player)
{
    if (player &&
        player->attacking &&
        player->attack &&
        player->attack->sprite) {
        sfRenderWindow_drawSprite(window, player->attack->sprite, NULL);
    }
    if (player &&
        !player->attacking &&
        player->sprite &&
        player->sprite->sprite) {
        sfRenderWindow_drawSprite(window, player->sprite->sprite, NULL);
    }
}
