/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** events.c
*/

#include "my_def.h"
#include "my.h"

static void move_cursor(sprite_t *cursor, sfVector2f mouse)
{
    if (cursor != NULL && cursor->sprite != NULL) {
        sfSprite_setPosition(cursor->sprite, mouse);
    }
}

static void play_click(sound_t *click, scene_t scene)
{
    if (scene != SCENE_OUTSIDE) {
        if (click != NULL && click->play != NULL) {
            sfSound_play(click->play);
        }
    }
}

static sfVector2f update_mouse_position(sfEvent *event, game_t *game)
{
    sfVector2f mouse = {0};

    switch (event->type) {
        case sfEvtMouseMoved:
            mouse = (sfVector2f){event->mouseMove.x, event->mouseMove.y};
            move_cursor(game->cursor, mouse);
            return mouse;
        case sfEvtMouseButtonPressed:
            mouse = (sfVector2f){event->mouseButton.x, event->mouseButton.y};
            play_click(game->sounds[SOUND_CLICK], game->scene);
            return mouse;
        case sfEvtMouseButtonReleased:
            mouse = (sfVector2f){event->mouseButton.x, event->mouseButton.y};
            return mouse;
        default:
            break;
    }
    return mouse;
}

static void redirect_events_drawer(game_t *game, sfEvent *event)
{
    switch (game->scene) {
        case SCENE_RESUME:
            analyse_resume_events(game, event);
            break;
        case SCENE_SHOP:
            analyse_shop_events(game, event);
            break;
        case SCENE_SHERIFF:
            analyse_sheriff_events(game, event);
            break;
        case SCENE_ROOM:
            analyse_room_events(game, event);
            break;
        case SCENE_BOSS:
            analyse_boss_events(game, event);
            break;
        default:
            break;
    }
}

static void redirect_events(game_t *game, sfEvent *event)
{
    switch (game->scene) {
        case SCENE_TITLE:
            analyse_title_events(game, event);
            break;
        case SCENE_SETTINGS:
            analyse_settings_events(game, event);
            break;
        case SCENE_SELECTION:
            analyse_selection_events(game, event);
            break;
        case SCENE_TUTO:
            analyse_tuto_events(game, event);
            break;
        case SCENE_SPAWN:
            analyse_spawn_events(game, event);
            break;
        default:
            redirect_events_drawer(game, event);
            break;
    }
}

void analyse_events(game_t *game, sfEvent *event)
{
    if (event->type != sfEvtClosed) {
        game->mouse = update_mouse_position(event, game);
        if (game->scene != SCENE_OUTSIDE) {
            redirect_events(game, event);
            game->help_displayed = false;
        } else {
            analyse_game_events(game, event);
        }
        if (is_game_scene(game->scene)) {
            analyse_inventory_events(game, event);
            analyse_pause_events(game, event);
        }
        if (event->type == sfEvtKeyPressed && event->key.code == sfKeyF2) {
            take_screenshot(game->window, game->sounds[SOUND_SHOT]);
        }
    } else {
        sfRenderWindow_close(game->window);
    }
}
