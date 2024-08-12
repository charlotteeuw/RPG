/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** inventory.c
*/

#include <stdlib.h>
#include "my.h"

const char *items_names[MAX_ITEMS] = {"Potion", "Sword", "Seeds"};

const char *items_paths[MAX_ITEMS] = {
    "./assets/images/potion.png",
    "./assets/images/sword.png",
    "./assets/images/seeds.png"
};

void (*items_actions[MAX_ITEMS])(quests_t *) = {
    increment_speed, NULL, NULL
};

static item_t *create_item(const char *filename, const char *name)
{
    item_t *item = malloc(sizeof(item_t));

    if (item != NULL) {
        item->quantity_text = create_text("0", sfWhite, 20);
        item->name = create_text(name, sfWhite, 25);
        item->img = create_sprite(filename);
        item->is_hover = false;
        item->quantity = 0;
    }
    return item;
}

static item_t **create_items(void)
{
    item_t **items = malloc(sizeof(item_t) * MAX_ITEMS);
    sfVector2f scale = {4.0, 4.0};

    for (enum e_items i = 0; items != NULL && i < MAX_ITEMS; i++) {
        items[i] = create_item(items_paths[i], items_names[i]);
        if (items[i] != NULL && items[i]->img != NULL) {
            sfSprite_setScale(items[i]->img->sprite, scale);
            center_sprite(items[i]->img->sprite);
            items[i]->action = items_actions[i];
        }
    }
    return items;
}

inventory_t *create_inventory(void)
{
    inventory_t *inventory = malloc(sizeof(inventory_t));
    sfVector2f position = {0.5, 0.5};

    if (inventory != NULL) {
        inventory->img = create_sprite("./assets/images/inventory.png");
        if (inventory->img != NULL) {
            center_sprite(inventory->img->sprite);
            sfSprite_setPosition(inventory->img->sprite, position);
        }
        inventory->items = create_items();
        inventory->is_open = false;
    }
    return inventory;
}

static void render_item(sfRenderWindow *window, item_t *item)
{
    if (item->img != NULL && item->img->sprite != NULL) {
        view_dynamic_drawsprite(window, item->img->sprite);
    }
    if (item->quantity_text != NULL) {
        view_dynamic_drawtext(window, item->quantity_text);
    }
    if (item->name != NULL && item->is_hover) {
        view_dynamic_drawtext(window, item->name);
    }
}

void render_inventory(sfRenderWindow *window, inventory_t *inventory)
{
    if (!inventory->is_open) {
        return;
    }
    view_dynamic_drawsprite(window, inventory->img->sprite);
    for (enum e_items i = 0; inventory->items != NULL && i < MAX_ITEMS; i++) {
        if (inventory->items[i] != NULL && inventory->items[i]->quantity > 0) {
            render_item(window, inventory->items[i]);
        }
    }
}

static void destroy_items(item_t **items)
{
    for (enum e_items i = 0; i < MAX_ITEMS; i++) {
        if (items[i]->img != NULL) {
            destroy_sprite(items[i]->img);
        }
        if (items[i]->name != NULL) {
            sfText_destroy(items[i]->name);
        }
        if (items[i]->quantity_text != NULL) {
            sfText_destroy(items[i]->quantity_text);
        }
    }
}

void destroy_inventory(inventory_t *inventory)
{
    if (inventory != NULL) {
        if (inventory->img != NULL) {
            destroy_sprite(inventory->img);
        }
        if (inventory->items != NULL) {
            destroy_items(inventory->items);
            free(inventory->items);
        }
        free(inventory);
    }
}
