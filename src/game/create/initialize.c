/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** initliaze.c
*/

#include "my_def.h"
#include <stdlib.h>
#include "my.h"

const char *sounds_list[MAX_SOUNDS] = {
    "./assets/sounds/screenshot.wav",
    "./assets/sounds/click.wav",
};

static void initialize_data_drawer(game_t *game)
{
    game->volumes[VOLUME_MUSIC] = 0.5;
    game->volumes[VOLUME_SOUND] = 0.5;
}

static void initialize_data(game_t *game)
{
    game->help = create_text("Press the tool key to enter", C_DARK_TEXT, 35);
    game->dialogue = create_sprite("./assets/images/dialogue.png");
    game->cursor = create_sprite("./assets/images/cursor.png");
    game->day_text = create_text("Day: 1", C_DARK_TEXT, 20);
    game->level = create_text("Level: 0", C_DARK_TEXT, 20);
    game->bg = create_sprite("./assets/images/title.png");
    game->cat = create_sprite("./assets/images/cat.png");
    game->framerate = create_text("0", C_DARK_TEXT, 20);
    game->keybinds = create_keybinds();
    game->framerate_displayed = true;
    game->clock = sfClock_create();
    game->help_displayed = false;
    game->fade = create_fade();
    game->scene = SCENE_TITLE;
    game->rain = init_rain();
    game->snow = init_snow();
    game->cat_is_dead = 1;
    game->is_day = true;
    game->day = 1;
}

static void initialize_npcs(game_t *game)
{
    game->npcs = malloc(sizeof(npc_t *) * 5);
    if (game->npcs != NULL) {
        game->npcs[0] = create_npc("./assets/images/npc1.png",
            (sfVector2f){14186, 9970});
        game->npcs[1] = create_npc("./assets/images/npc2.png",
            (sfVector2f){14168, 11170});
        game->npcs[2] = create_npc("./assets/images/npc3.png",
            (sfVector2f){10252, 9136});
        game->npcs[3] = create_npc("./assets/images/npc4.png",
            (sfVector2f){10648, 10298});
        game->npcs[4] = NULL;
    }
    game->zombies = malloc(sizeof(zombie_t *) * 11);
    for (size_t i = 0; game->zombies != NULL && i < 10; i++) {
        game->zombies[i] = create_zombie();
    }
    game->zombies[10] = NULL;
}

static sprite_t *create_healthbar(void)
{
    sprite_t *healthbar = create_sprite("./assets/images/health.png");
    sfVector2f pos = {0.02, 0.98};
    sfVector2f origin = {0, 0};
    sfFloatRect bounds;
    sfIntRect rect = {0, 0, 350, 118};

    if (healthbar != NULL && healthbar->sprite != NULL) {
        sfSprite_setTextureRect(healthbar->sprite, rect);
        sfSprite_setPosition(healthbar->sprite, pos);
        bounds = sfSprite_getLocalBounds(healthbar->sprite);
        origin.y = bounds.height;
        sfSprite_setOrigin(healthbar->sprite, origin);
    }
    return healthbar;
}

static player_t *initialize_player(void)
{
    player_t *player = malloc(sizeof(player_t));

    if (player != NULL) {
        player->health_bar = create_healthbar();
        player->sprite = create_sprite("./assets/images/man.png");
        player->attack = create_sprite("./assets/images/attack_girl.png");
        player->inventory = create_inventory();
        player->quests = create_quests();
        player->clock = sfClock_create();
        player->name = my_strdup("Jean");
        player->pause = create_pause();
        player->experience = 0;
        player->moving = true;
        player->attacking = false;
        player->health = 100;
        player->male = false;
        player->level = 0;
        player->damage = 0;
    }
    return player;
}

static void redirect_game_initialization(game_t *game)
{
    if (game->help != NULL) {
        center_text_origin(game->help);
        sfText_setPosition(game->help, (sfVector2f){0.5, 0.75});
    }
}

static void initialize_game(game_t *game)
{
    for (size_t i = 0; i < MAX_SOUNDS; i++) {
        game->sounds[i] = create_sound(sounds_list[i]);
    }
    if (game->framerate != NULL) {
        sfText_setPosition(game->framerate, (sfVector2f){0.02, 0.06});
    }
    if (game->title != NULL && game->title->music != NULL) {
        sfMusic_play(game->title->music);
    }
    if (game->cat != NULL && game->cat->sprite != NULL) {
        sfSprite_setScale(game->cat->sprite, (sfVector2f){2, 2});
    }
    if (game->level != NULL) {
        sfText_setPosition(game->level, (sfVector2f){0.02, 0.02});
    }
    if (game->day_text != NULL) {
        sfText_setPosition(game->day_text, (sfVector2f){0.02, 0.04});
    }
    redirect_game_initialization(game);
}

void redirect_initialization(game_t *game, enum e_steps step)
{
    switch (step) {
        case INIT_DATA:
            initialize_data(game);
            initialize_data_drawer(game);
            break;
        case INIT_NPCS:
            initialize_npcs(game);
            break;
        case INIT_PLAYER:
            game->player = initialize_player();
            break;
        case INIT_GAME:
            initialize_game(game);
            break;
        default:
            initialize_scene(game, step);
            break;
    }
}
