/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** utils.c
*/

#include "my.h"

const scene_t game_scene[7] = {
    SCENE_OUTSIDE, SCENE_ROOM, SCENE_SHERIFF, SCENE_SHOP, SCENE_SPAWN,
    SCENE_TUTO, SCENE_BOSS
};

bool is_game_scene(scene_t scene)
{
    for (scene_t i = 0; i < 7; i++) {
        if (scene != game_scene[i]) {
            continue;
        }
        return true;
    }
    return false;
}
