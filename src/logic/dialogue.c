/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** dialogue.c
*/

#include <stdlib.h>
#include <string.h>
#include "my_def.h"
#include "my.h"

static void replace(char *name, char *result, int *j, int *k)
{
    while (name[*j] != '\0') {
        result[*k] = name[*j];
        (*k)++;
        (*j)++;
    }
}

static void skip_var(char *buffer, int *i)
{
    while (buffer[*i] != ' ' && buffer[*i] != '\0')
        (*i)++;
}

static char *replace_name(char *buffer, char *name)
{
    char *result = malloc(sizeof(char) * (my_strlen(buffer) +
        my_strlen(name) + 1));
    int j = 0;
    int k = 0;

    for (int i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == '$') {
            replace(name, result, &j, &k);
            skip_var(buffer, &i);
        } else {
            result[k] = buffer[i];
            k++;
        }
    }
    result[k] = '\0';
    return result;
}

void draw_dialogue(sfText *text, sfRenderWindow *window)
{
    if (text != NULL) {
        sfRenderWindow_drawText(window, text, NULL);
    }
}

sfText *next_paragraph(sfText *text, char *file, char *name)
{
    static size_t paragraph_nb = 0;
    static char *buffer = NULL;
    char **arr = NULL;

    if (file != NULL) {
        paragraph_nb = 0;
        buffer = my_open(file);
        buffer = replace_name(buffer, name);
    }
    if (buffer == NULL)
        return NULL;
    arr = my_splitstr(buffer, "@");
    if (arr[paragraph_nb] == NULL || text == NULL)
        return NULL;
    sfText_setString(text, arr[paragraph_nb]);
    paragraph_nb++;
    return text;
}

sfText *create_dialogue_text(char *file, char *name)
{
    sfText *text = sfText_create();
    sfFont *font = sfFont_createFromFile("./assets/fonts/merriweather.ttf");

    sfText_setFont(text, font);
    sfText_setColor(text, C_DARK_TEXT);
    sfText_setCharacterSize(text, 20);
    if (text != NULL && file != NULL)
        next_paragraph(text, file, name);
    return text;
}

sfText *handle_dialogue(game_t *game, sfEvent *event, sfVector2f position,
    sfText *text)
{
    if (text == NULL) {
        return NULL;
    }
    if (event->type == sfEvtKeyReleased && event->key.code == 57) {
        text = next_paragraph(text, NULL, game->player->name);
    }
    if (text != NULL) {
        sfText_setPosition(text, position);
    }
    return text;
}
