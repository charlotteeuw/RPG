/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** create.c
*/

#include "my_def.h"
#include <stdlib.h>
#include <math.h>
#include "my.h"

void render_npcs(sfRenderWindow *window, npc_t **npcs)
{
    for (size_t i = 0; npcs[i] != NULL; i++) {
        if (npcs[i]->sprite != NULL && npcs[i]->sprite->sprite != NULL) {
            sfRenderWindow_drawSprite(window, npcs[i]->sprite->sprite, NULL);
        }
    }
}

void move_npc(npc_t *npc)
{
    static sfClock *clock = NULL;
    sfTime time;
    float seconds;

    if (clock == NULL)
        clock = sfClock_create();
    time = sfClock_getElapsedTime(clock);
    seconds = sfTime_asSeconds(time);
    npc->position.y += sin(seconds) * 2;
    sfSprite_setPosition(npc->sprite->sprite, npc->position);
}

npc_t *create_npc(const char *file, sfVector2f position)
{
    npc_t *npc = malloc(sizeof(npc_t));

    if (npc != NULL && file != NULL) {
        npc->sprite = create_sprite(file);
        sfSprite_setPosition(npc->sprite->sprite, position);
        sfSprite_setScale(npc->sprite->sprite, (sfVector2f){5, 5});
        npc->position = position;
    }
    return npc;
}
