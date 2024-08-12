/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** analyse_inventory.c
*/

#include "my.h"

static void is_inventory_hover(game_t *game, sfVector2f pos)
{
    bool in = false;
    inventory_t *inventory = game->player->inventory;

    for (enum e_items i = 0; inventory->items != NULL && i < MAX_ITEMS; i++) {
        if (inventory->items[i] != NULL) {
            in = view_is_in_sprite(game->window,
                inventory->items[i]->img->sprite, pos.x, pos.y);
            inventory->items[i]->is_hover = in;
        }
    }
}

static void is_inventory_released(game_t *game, sfVector2f pos)
{
    item_t *actual = NULL;
    bool in = false;

    if (!game->player->inventory->items) {
        return;
    }
    for (enum e_items i = 0; i < MAX_ITEMS; i++) {
        if (!game->player->inventory->items[i]) {
            continue;
        }
        actual = game->player->inventory->items[i];
        in = view_is_in_sprite(game->window,
            actual->img->sprite, pos.x, pos.y);
        if (in) {
            use_item(game, i);
        }
    }
}

static void is_inventory_used(game_t *game, sfEvent *event)
{
    sfVector2f pos = {0.0, 0.0};

    switch (event->type) {
        case sfEvtMouseButtonReleased:
            pos = game->mouse;
            is_inventory_released(game, pos);
            break;
        case sfEvtMouseMoved:
            pos = game->mouse;
            is_inventory_hover(game, pos);
            break;
        default:
            break;
    }
}

void analyse_inventory_events(game_t *game, sfEvent *event)
{
    if (event->type != sfEvtKeyReleased) {
        if (game->player->inventory->is_open) {
            is_inventory_used(game, event);
        }
    } else {
        if (event->key.code != game->keybinds[BIND_INV]) {
            return;
        }
        game->player->inventory->is_open = !game->player->inventory->is_open;
        switch_player_movement(game->player, SWITCH_MOVING);
        if (game->player->quests->is_open) {
            game->player->quests->is_open = false;
        }
        if (game->player->pause->is_open) {
            game->player->pause->is_open = false;
        }
    }
}
