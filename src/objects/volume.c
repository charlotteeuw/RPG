/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** volume.c
*/

#include <stdlib.h>
#include "my.h"

void update_volumes(game_t *game)
{
    for (size_t i = 0; game != NULL && i < MAX_SOUNDS; i++) {
        if (game->sounds[i] != NULL && game->sounds[i]->play) {
            sfSound_setVolume(game->sounds[i]->play,
                game->volumes[VOLUME_SOUND] * 100.0);
        }
    }
    if (game != NULL && game->title != NULL && game->title->music != NULL) {
        sfMusic_setVolume(game->title->music,
            game->volumes[VOLUME_MUSIC] * 100.0);
    }
}

sfMusic *create_music(char *file)
{
    sfMusic *new = sfMusic_createFromFile(file);

    if (new != NULL) {
        sfMusic_setLoop(new, sfTrue);
        sfMusic_setVolume(new, 50.0);
    }
    return new;
}

sound_t *create_sound(char const *file)
{
    sound_t *new = malloc(sizeof(sound_t));

    if (!new) {
        return NULL;
    }
    new->play = sfSound_create();
    if (new->play != NULL) {
        new->buffer = sfSoundBuffer_createFromFile(file);
        if (new->buffer != NULL) {
            sfSound_setBuffer(new->play, new->buffer);
            sfSound_setVolume(new->play, 50.0);
        } else {
            sfSound_destroy(new->play);
            free(new);
            return NULL;
        }
    } else {
        free(new);
    }
    return new;
}

void destroy_sound(sound_t *sound)
{
    if (sound != NULL) {
        if (sound->play != NULL) {
            sfSound_destroy(sound->play);
        }
        if (sound->buffer != NULL) {
            sfSoundBuffer_destroy(sound->buffer);
        }
        free(sound);
    }
}
