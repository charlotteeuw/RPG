/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** create.c
*/

#include "my_def.h"
#include <stdlib.h>
#include "my.h"

const char *steps_str[LAST_INIT + 1] = {
    "Creating the window..",
    "Creating the necessary data..",
    "Initializing the player..",
    "Initializing the user interface..",
    "Initializing the outside..",
    "Initializing the rooms..",
    "Initializing the NPCs..",
    "Setting up game components..",
    "Initialization done",
};

static void manage_window_events(sfRenderWindow *window, sfEvent *events)
{
    if (events->type != sfEvtClosed) {
    } else {
        sfRenderWindow_close(window);
    }
}

static void display_loading_screen(sfRenderWindow *window,
    sfText *text, progress_t *progress)
{
    sfRenderWindow_clear(window, sfBlack);
    if (text != NULL) {
        sfRenderWindow_drawText(window, text, NULL);
    }
    if (progress != NULL && progress->background != NULL) {
        sfRenderWindow_drawRectangleShape(window, progress->background, NULL);
    }
    if (progress != NULL && progress->foreground != NULL) {
        sfRenderWindow_drawRectangleShape(window, progress->foreground, NULL);
    }
    sfRenderWindow_display(window);
}

static void update_loading_text(sfText *text, enum e_steps step)
{
    sfFloatRect bounds = {0.0, 0.0, 0.0, 0.0};
    sfVector2f center = {0.0, 0.0};

    if (text != NULL) {
        sfText_setString(text, steps_str[step]);
        bounds = sfText_getGlobalBounds(text);
        center.x = (1920 - bounds.width) / 2;
        center.y = (1080 - bounds.height) / 2;
        sfText_setPosition(text, center);
    }
}

static bool load_game(game_t *game, sfText *text, progress_t *progress)
{
    enum e_steps step = INIT_WINDOW;
    sfVector2f size = {75.0, 15.0};

    for (sfEvent events = {0}; sfRenderWindow_isOpen(game->window); step++) {
        if (step > LAST_INIT) {
            break;
        }
        while (sfRenderWindow_pollEvent(game->window, &events)) {
            manage_window_events(game->window, &events);
        }
        update_loading_text(text, step);
        display_loading_screen(game->window, text, progress);
        sfRectangleShape_setSize(progress->foreground, size);
        redirect_initialization(game, step);
        size.x += 75.0;
    }
    return step > LAST_INIT;
}

bool create_game(game_t *game)
{
    sfText *text = create_text("", C_LIGHT_TEXT, 25);
    sfVector2f progress_pos = {660, 600};
    sfVector2f progress_size = {600, 15};
    progress_t *progress = create_progress(progress_pos, progress_size);
    sfVector2f text_pos = {850, 540};
    bool success = false;

    game->window = create_window(sfFullscreen, 1920, 1080, DEFAULT_FRAMERATE);
    if (game->window != NULL && text != NULL && progress != NULL) {
        sfRenderWindow_setMouseCursorVisible(game->window, sfFalse);
        sfText_setPosition(text, text_pos);
        success = load_game(game, text, progress);
    }
    if (text != NULL) {
        sfText_destroy(text);
    }
    if (progress != NULL) {
        destroy_progress(progress);
    }
    return success;
}
