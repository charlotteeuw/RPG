/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** render_game.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

static void draw_dialogues(sfRenderWindow *window, game_t *game, int dialogue)
{
    if (game->outside->is_dialogue == 1 && dialogue == 0 &&
        !game->player->moving) {
        draw_dialogue(game->outside->text, window);
    }
    if (game->outside->is_dialogue == 1 && game->outside->night == 1) {
        if (game->outside->night1 != NULL) {
            draw_dialogue(game->outside->night1, window);
        }
    }
    if (game->outside->is_dialogue == 1 &&
        game->player->quests->fifth_quest == 1) {
        if (game->outside->final_text != NULL) {
            draw_dialogue(game->outside->final_text, window);
        }
    }
}

static void draw_dialogue_assets2(sfRenderWindow *window, game_t *game,
    sfVector2f center, int dialogue)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->outside->icon != NULL && game->outside->is_dialogue == 1
        && (dialogue == 0 || game->outside->night == 1 ||
        game->player->quests->fifth_quest)) {
        sfSprite_setPosition(game->outside->icon->sprite,
            (sfVector2f){bottom.x + 40, bottom.y + 50});
        sfRenderWindow_drawSprite(window, game->outside->icon->sprite, NULL);
    }
    draw_dialogues(window, game, dialogue);
}

static void draw_dialogue_assets(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (!game->outside->is_dialogue) {
        game->outside->passed = 1;
    }
    if (game->outside->dialogue != NULL && game->outside->is_dialogue == 1
        && (!game->outside->passed || game->outside->night ||
        game->player->quests->fifth_quest)) {
        sfSprite_setPosition(game->outside->dialogue->sprite, bottom);
        sfRenderWindow_drawSprite(window, game->outside->dialogue->sprite,
            NULL);
    }
    draw_dialogue_assets2(window, game, center, game->outside->passed);
}

static void render_map(sfRenderWindow *window, game_t *game)
{
    if (!game->is_day) {
        sfRenderWindow_drawSprite(window, game->outside->night_bg->sprite,
            NULL);
        return;
    }
    if (0.6 * DAY_DURATION < game->current_time_in_day &&
        game->current_time_in_day < DAY_DURATION) {
        sfRenderWindow_drawSprite(window, game->outside->sunset_bg->sprite,
            NULL);
        return;
    }
    if (game->is_day) {
        sfRenderWindow_drawSprite(window, game->outside->bg->sprite, NULL);
        return;
    }
}

static void first_night(game_t *game)
{
    if (game->day == 1 && !game->is_day && !game->outside->passed_night) {
        game->outside->is_dialogue = 1;
        game->outside->night = 1;
        game->outside->night1 =
            create_dialogue_text("./assets/dialogue/first_night.txt",
                game->player->name);
        game->outside->passed_night = 1;
    }
    if (game->outside->passed_night && game->outside->night1 == NULL) {
        game->outside->is_dialogue = 0;
        game->outside->night = 0;
    }
}

static void end(game_t *game)
{
    if (game->player->quests->fifth_quest && !game->outside->passed_end) {
        game->outside->is_dialogue = 1;
        game->outside->final_text =
            create_dialogue_text("./assets/dialogue/end.txt",
            game->player->name);
        game->outside->passed_end = 1;
    }
    if (game->outside->passed_end && game->outside->final_text == NULL) {
        game->outside->is_dialogue = 0;
        game->scene = SCENE_TITLE;
    }
}

static void draw_weather(sfRenderWindow *window, game_t *game)
{
    if ((game->day == 2 || game->day == 5) && !game->is_day)
        draw_rain(window, game->rain);
    if ((game->day == 3 || game->day == 4) && !game->is_day)
        draw_snow(window, game->snow);
}

void render_outside(game_t *game)
{
    sfRenderWindow *window = game->window;
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);

    render_map(game->window, game);
    render_player(game->window, game->player);
    if (game->cat != NULL && game->cat_is_dead == 0) {
        sfRenderWindow_drawSprite(window, game->cat->sprite, NULL);
    }
    if (game->outside->up_bg->sprite != NULL) {
        sfRenderWindow_drawSprite(window, game->outside->up_bg->sprite, NULL);
    }
    first_night(game);
    end(game);
    draw_dialogue_assets(window, game, center);
    draw_weather(window, game);
}
