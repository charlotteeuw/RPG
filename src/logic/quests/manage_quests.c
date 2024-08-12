/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** quests.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"
#include <stdio.h>

void increment_speed(quests_t *player)
{
    player->fast = 800;
}

static void init_quests2(quests_t *quests)
{
    sfText_setPosition(quests->quests, (sfVector2f){0.29, 0.225});
    sfText_setPosition(quests->quest1, (sfVector2f){0.285, 0.3});
    sfText_setPosition(quests->quest2, (sfVector2f){0.285, 0.3});
    sfText_setPosition(quests->quest3, (sfVector2f){0.285, 0.35});
    sfText_setPosition(quests->quest4, (sfVector2f){0.285, 0.3});
    sfText_setPosition(quests->quest5, (sfVector2f){0.285, 0.35});
    quests->first_quest = 0;
    quests->second_quest = 0;
    quests->third_quest = 0;
    quests->fourth_quest = 0;
    quests->fifth_quest = 0;
}

static void init_quests(quests_t *quests)
{
    quests->quests = create_text("Quests:", C_DARK_TEXT, 40);
    quests->quest1 = create_text("Visit Tissia in her shop to get seeds.",
        C_DARK_TEXT, 20);
    quests->quest2 = create_text("The sheriff has something to tell you...",
        C_DARK_TEXT, 20);
    quests->quest3 = create_text("You're hurt. Go get healed at Natty's.",
        C_DARK_TEXT, 20);
    quests->quest4 = create_text("Go back to your house.",
        C_DARK_TEXT, 20);
    quests->quest5 =
        create_text("Find out who hurt the cat...",
        C_DARK_TEXT, 20);
    init_quests2(quests);
}

static void init_sprites(quests_t *quest)
{
    sfVector2f position = {0.5, 0.5};
    sfVector2f checkbox_pos = {0.485, 0.31};

    if (quest->img != NULL && quest->unchecked != NULL &&
        quest->checked != NULL) {
        center_sprite(quest->img->sprite);
        sfSprite_setPosition(quest->img->sprite, position);
        sfSprite_setScale(quest->img->sprite, (sfVector2f){2, 2});
        center_sprite(quest->unchecked->sprite);
        sfSprite_setPosition(quest->unchecked->sprite, checkbox_pos);
        sfSprite_setScale(quest->unchecked->sprite, (sfVector2f){0.12, 0.12});
        center_sprite(quest->checked->sprite);
        sfSprite_setPosition(quest->checked->sprite, checkbox_pos);
        sfSprite_setScale(quest->checked->sprite, (sfVector2f){0.12, 0.12});
    }
}

static void init_stats(quests_t *quests)
{
    quests->stats = create_text("Player statistics:", C_DARK_TEXT, 40);
    quests->experience = create_text("Experience:", C_DARK_TEXT, 20);
    quests->level = create_text("Level:", C_DARK_TEXT, 20);
    quests->life = create_text("Life:", C_DARK_TEXT, 20);
    quests->damage = create_text("Damage:", C_DARK_TEXT, 20);
    quests->speed = create_text("Speed:", C_DARK_TEXT, 20);
    sfText_setPosition(quests->stats, (sfVector2f){0.525, 0.225});
    sfText_setPosition(quests->experience, (sfVector2f){0.525, 0.3});
    sfText_setPosition(quests->level, (sfVector2f){0.525, 0.35});
    sfText_setPosition(quests->life, (sfVector2f){0.525, 0.4});
    sfText_setPosition(quests->damage, (sfVector2f){0.525, 0.45});
    sfText_setPosition(quests->speed, (sfVector2f){0.525, 0.5});
}

quests_t *create_quests(void)
{
    quests_t *quest = malloc(sizeof(quests_t));

    if (quest != NULL) {
        quest->img = create_sprite("./assets/images/quests.png");
        quest->unchecked = create_sprite("./assets/images/checkbox.png");
        quest->checked = create_sprite("./assets/images/checkbox_checked.png");
        init_sprites(quest);
        init_quests(quest);
        init_stats(quest);
        quest->is_open = false;
        quest->fast = 300;
    }
    return quest;
}

void analyse_experience(player_t *player)
{
    if (player->experience >= 20 && player->experience < 40)
        player->level = 1;
    if (player->experience >= 40 && player->experience < 60)
        player->level = 2;
    if (player->experience >= 60 && player->experience < 90)
        player->level = 3;
    if (player->experience >= 90 && player->experience < 130)
        player->level = 4;
    if (player->experience >= 130 && player->experience < 200)
        player->level = 5;
    if (player->experience >= 200 && player->experience < 300)
        player->level = 6;
    if (player->experience >= 300 && player->experience < 500)
        player->level = 7;
    player->damage = 5 * player->level;
}

void analyse_quests_events(game_t *game, sfEvent *event)
{
    if (event->type != sfEvtKeyReleased) {
        return;
    }
    if (event->key.code == game->keybinds[BIND_QUESTS]) {
        game->player->quests->is_open = !game->player->quests->is_open;
        switch_player_movement(game->player, SWITCH_MOVING);
        if (game->player->inventory->is_open) {
            game->player->inventory->is_open = false;
        }
        if (game->player->pause->is_open) {
            game->player->pause->is_open = false;
        }
    }
}

void destroy_quests(quests_t *quests)
{
    if (quests != NULL) {
        destroy_sprite(quests->img);
        free(quests);
    }
}
