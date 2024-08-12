/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** particles.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"
#include <stdio.h>

rain_t *init_rain(void)
{
    rain_t *particles = malloc(sizeof(rain_t) * 1000);

    for (size_t i = 0; i < 1000; i++) {
        particles[i].position = (sfVector2f){rand() % 1920, rand() % 1080};
        particles[i].speed = 500.0;
        particles[i].sprite = create_sprite("./assets/images/raindrop.png");
        sfSprite_setPosition(particles[i].sprite->sprite,
            particles[i].position);
    }
    return particles;
}

snow_t *init_snow(void)
{
    snow_t *particles = malloc(sizeof(snow_t) * 500);

    for (size_t i = 0; i < 500; i++) {
        particles[i].position = (sfVector2f){rand() % 1920, rand() % 1080};
        particles[i].speed = 300.0;
        particles[i].sprite = create_sprite("./assets/images/snow.png");
        sfSprite_setPosition(particles[i].sprite->sprite,
            particles[i].position);
    }
    return particles;
}

void update_rain(rain_t *particles, float time)
{
    for (size_t i = 0; i < 1000; i++) {
        particles[i].position.y += particles[i].speed * time;
        if (particles[i].position.y > 1080) {
            particles[i].position.y = 0;
            particles[i].position.x = rand() % 1920;
        }
        sfSprite_setPosition(particles[i].sprite->sprite,
            particles[i].position);
    }
}

void update_snow(snow_t *particles, float time)
{
    for (size_t i = 0; i < 500; i++) {
        particles[i].position.y += particles[i].speed * time;
        if (particles[i].position.y > 1080) {
            particles[i].position.y = 0;
            particles[i].position.x = rand() % 1920;
        }
        sfSprite_setPosition(particles[i].sprite->sprite,
            particles[i].position);
    }
}
