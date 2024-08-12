/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** user_inventory.c
*/

#include <stdio.h>
#include "my.h"

static void set_inventory_positions(inventory_t *inventory)
{
    sfVector2f item_pos = {0.0, 0.350};
    sfVector2f name_pos = {0.0, 0.250};
    sfVector2f q_pos = {0.0, 0.370};
    float n = 0;

    for (enum e_items i = 0; i < MAX_ITEMS; i++) {
        if (inventory->items[i] != NULL && inventory->items[i]->quantity > 0) {
            item_pos.x = 0.310 + (n * 0.055);
            q_pos.x = item_pos.x + 0.005;
            name_pos.x = item_pos.x + 0.015;
            sfText_setPosition(inventory->items[i]->name, name_pos);
            sfText_setPosition(inventory->items[i]->quantity_text, q_pos);
            sfSprite_setPosition(inventory->items[i]->img->sprite, item_pos);
            n++;
        }
    }
}

static void update_item_quantity(sfText *text, unsigned int quantity)
{
    char str[15] = {0};

    sprintf(str, "%u", quantity);
    sfText_setString(text, str);
}

void add_item_to_inventory(inventory_t *inventory,
    enum e_items item, unsigned int quantity)
{
    if (!inventory) {
        return;
    }
    if (quantity < 1) {
        return;
    }
    if (inventory->items != NULL && inventory->items[item] != NULL) {
        inventory->items[item]->quantity += quantity;
        update_item_quantity(inventory->items[item]->quantity_text,
            inventory->items[item]->quantity);
        set_inventory_positions(inventory);
    }
}

void remove_item_from_inventory(inventory_t *inventory,
    enum e_items item, unsigned int quantity)
{
    if (!inventory) {
        return;
    }
    if (quantity < 1) {
        return;
    }
    if (inventory->items != NULL && inventory->items[item] != NULL) {
        if (inventory->items[item]->quantity >= quantity) {
            inventory->items[item]->quantity -= quantity;
            update_item_quantity(inventory->items[item]->quantity_text,
                inventory->items[item]->quantity);
            set_inventory_positions(inventory);
        }
    }
}

void use_item(game_t *game, enum e_items item)
{
    if (!game->player->inventory->items[item]) {
        return;
    }
    if (game->player->inventory->items[item]->quantity > 0) {
        if (game->player->inventory->items[item]->action != NULL) {
            game->player->inventory->items[item]->action(game->player->quests);
        }
        remove_item_from_inventory(game->player->inventory, item, 1);
    }
}
