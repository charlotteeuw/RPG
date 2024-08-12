/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** save.c
*/

#include <stdlib.h>
#include <dirent.h>
#include "my_def.h"
#include <string.h>
#include "my.h"

resume_t *create_resume(void)
{
    resume_t *resume = malloc(sizeof(resume_t));

    if (resume != NULL) {
        resume->back = create_button("BACK",
            (sfVector2f){70.0, 1000.0}, (sfVector2f){0.5, 1}, switch_to_title);
        resume->plate = create_sprite("./assets/images/plate.png");
        if (resume->plate != NULL && resume->plate->sprite != NULL) {
            center_sprite(resume->plate->sprite);
            sfSprite_setScale(resume->plate->sprite, (sfVector2f){2.0, 3.5});
            sfSprite_setPosition(resume->plate->sprite,
                (sfVector2f){960.0, 540.0});
        }
        resume->title = create_text("Your backups", C_DARK_TEXT, 40);
        if (resume->title != NULL) {
            set_text_position(resume->title, (sfVector2f){960.0, 140.0});
        }
        resume->saves = NULL;
    }
    return resume;
}

void render_resume(game_t *game)
{
    sfRenderWindow *window = game->window;
    resume_t *resume = game->resume;

    if (resume != NULL && window != NULL) {
        if (game->bg != NULL) {
            sfRenderWindow_drawSprite(window, game->bg->sprite, NULL);
        }
        if (resume->plate != NULL) {
            sfRenderWindow_drawSprite(window, resume->plate->sprite, NULL);
        }
        if (resume->title != NULL) {
            sfRenderWindow_drawText(window, resume->title, NULL);
        }
        if (resume->back != NULL) {
            render_button(window, resume->back);
        }
        for (list_t *temp = resume->saves; temp != NULL; temp = temp->next) {
            render_button(window, temp->data);
        }
    }
}

void destroy_resume(resume_t *resume)
{
    if (resume != NULL) {
        if (resume->plate != NULL) {
            destroy_sprite(resume->plate);
        }
        if (resume->title != NULL) {
            destroy_text(resume->title);
        }
        if (resume->saves != NULL) {
            destroy_list(resume->saves, destroy_button);
        }
        if (resume->back != NULL) {
            destroy_button(resume->back);
        }
        free(resume);
    }
}

void analyse_resume_events(game_t *game, sfEvent *event)
{
    if (event->type == sfEvtKeyPressed && event->key.code == sfKeyEscape) {
        sfSound_play(game->sounds[SOUND_CLICK]->play);
        switch_to_title(game, NULL);
    }
    if (game->resume->back != NULL) {
        analyse_button_events(game, event, game->resume->back);
    }
    for (list_t *temp = game->resume->saves;
        temp != NULL; temp = temp->next) {
        if (temp->data != NULL) {
            analyse_button_events(game, event, temp->data);
        }
    }
}

static void create_save_buttons(list_t **head, DIR *directory)
{
    struct dirent *entry = readdir(directory);
    sfVector2f position = {960.0, 200.0};
    sfVector2f scale = {1.8, 0.8};
    char *dot = NULL;

    for (button_t *button = NULL; entry != NULL; entry = readdir(directory)) {
        dot = strrchr(entry->d_name, '.');
        if (!dot) {
            continue;
        }
        if (strcmp(dot, ".save") != 0) {
            continue;
        }
        dot[0] = '\0';
        button = create_button(entry->d_name, position, scale, resume_game);
        if (button != NULL) {
            append_to_list(head, button);
            position.y += 70.0;
        }
    }
}

void switch_to_resume(game_t *game, __attribute__((unused)) button_t *button)
{
    DIR *directory = NULL;

    if (game->resume != NULL) {
        if (game->resume->saves != NULL) {
            destroy_list(game->resume->saves, destroy_button);
            game->resume->saves = NULL;
        }
        directory = opendir(".backups");
        if (directory != NULL) {
            create_save_buttons(&game->resume->saves, directory);
            closedir(directory);
        }
        game->scene = SCENE_RESUME;
    }
}
