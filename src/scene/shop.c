/*
** EPITECH PROJECT, 2024
** RPG
** File description:
** shop.c
*/

#include <stdlib.h>
#include "my_def.h"
#include "my.h"

static void set_end_of_interaction(game_t *game, int *dialogue,
    int *interaction)
{
    static int do_once = 1;

    if (game->shop->text == NULL && do_once == 1) {
        game->shop->passed = 1;
        *dialogue = 0;
        *interaction = 0;
        game->shop->is_dialogue = 0;
        game->player->experience += 20;
        game->player->quests->first_quest = 1;
        add_item_to_inventory(game->player->inventory, ITEM_SEEDS, 1);
        do_once = 0;
    }
}

static void analyse_first_interaction(game_t *game, sfEvent *event,
    int *dialogue, int *interaction)
{
    const sfView *view = sfRenderWindow_getView(game->window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = {center.x - 100, center.y + 370};

    if (game->shop->passed == 1)
        return;
    game->shop->is_dialogue = 1;
    if (game->shop->dialogue != NULL) {
        game->shop->text = handle_dialogue(game, event, pos, game->shop->text);
    }
    set_end_of_interaction(game, dialogue, interaction);
}

void analyse_shop_events(game_t *game, __attribute__((unused)) sfEvent *event)
{
    sfVector2f position = sfSprite_getPosition(game->player->sprite->sprite);
    static int dialogue = 1;
    static int interaction = 0;

    if ((position.x >= 800 && position.x <= 900) &&
        (position.y >= 300 && position.y <= 450) &&
        game->keybinds[BIND_TOOL] == event->key.code &&
        event->type == sfEvtKeyReleased) {
            interaction = 1;
    }
    if (dialogue == 1 && interaction == 1)
        analyse_first_interaction(game, event, &dialogue, &interaction);
    if (position.y >= 1000)
        start_game(game, (sfVector2f){4778.0, 8443.0});
}

static void draw_dialogue_assets2(sfRenderWindow *window, game_t *game,
    sfVector2f center, int dialogue)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};

    if (game->shop->icon != NULL && game->shop->is_dialogue == 1
        && dialogue == 1) {
        sfSprite_setPosition(game->shop->icon->sprite,
            (sfVector2f){bottom.x + 40, bottom.y + 50});
        sfRenderWindow_drawSprite(window, game->shop->icon->sprite, NULL);
    }
    if (game->shop->is_dialogue == 1 && dialogue == 1) {
        draw_dialogue(game->shop->text, window);
    }
}

static void draw_dialogue_assets(sfRenderWindow *window, game_t *game,
    sfVector2f center)
{
    sfVector2f bottom = {center.x - 300, center.y + 300};
    static int dialogue = 1;

    if (game->shop->passed == 1)
        return;
    if (!game->shop->is_dialogue)
        dialogue = 0;
    else
        dialogue = 1;
    if (game->shop->dialogue != NULL && game->shop->is_dialogue == 1
        && dialogue == 1) {
        sfSprite_setPosition(game->shop->dialogue->sprite, bottom);
        sfRenderWindow_drawSprite(window, game->shop->dialogue->sprite, NULL);
    }
    draw_dialogue_assets2(window, game, center, dialogue);
}

void render_shop(game_t *game)
{
    sfRenderWindow *window = game->window;
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);

    if (game->shop->bg != NULL)
        sfRenderWindow_drawSprite(window, game->shop->bg->sprite, NULL);
    if (game->player->sprite != NULL)
        sfRenderWindow_drawSprite(window, game->player->sprite->sprite, NULL);
    if (game->cat != NULL && game->cat_is_dead == 0)
        sfRenderWindow_drawSprite(window, game->cat->sprite, NULL);
    if (game->shop->npc != NULL) {
        sfRenderWindow_drawSprite(window, game->shop->npc->sprite, NULL);
    }
    draw_dialogue_assets(window, game, center);
}

void destroy_shop(shop_t *shop)
{
    if (shop->bg != NULL) {
        destroy_sprite(shop->bg);
    }
    if (shop->npc != NULL) {
        destroy_sprite(shop->npc);
    }
    if (shop->dialogue != NULL) {
        destroy_sprite(shop->dialogue);
    }
    if (shop->icon != NULL) {
        destroy_sprite(shop->icon);
    }
    free(shop);
}

shop_t *create_shop(void)
{
    shop_t *shop = malloc(sizeof(shop_t));

    if (shop != NULL) {
        shop->passed = 0;
        shop->bg = create_sprite("./assets/images/shop.png");
        shop->collision = sfImage_createFromFile(
            "./assets/images/shop_collision.png"
        );
        shop->npc = create_sprite("./assets/images/tissia.png");
        shop->dialogue = create_sprite("./assets/images/dialogue.png");
        shop->icon = create_sprite("./assets/images/tissia_icon.png");
        sfSprite_setScale(shop->dialogue->sprite, (sfVector2f){3, 3});
        sfSprite_setScale(shop->icon->sprite, (sfVector2f){0.7, 0.7});
    }
    return shop;
}

void switch_to_shop(game_t *game)
{
    sfIntRect frame = {0, 0, 117, 141};
    sfVector2f spawn_pos = {900, 980};

    game->scene = SCENE_SHOP;
    game->shop->is_dialogue = 0;
    game->shop->text =
        create_dialogue_text("./assets/dialogue/getting_seeds.txt",
            game->player->name);
    game->shop->frame = frame;
    sfSprite_setTextureRect(game->shop->npc->sprite, frame);
    sfSprite_setPosition(game->player->sprite->sprite, spawn_pos);
    sfSprite_setPosition(game->shop->npc->sprite, (sfVector2f){850, 220});
    setposition_view(game->window, spawn_pos);
}
