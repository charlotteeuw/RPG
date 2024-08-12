/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** view_sprite.c
*/

#include <my.h>

void view_drawsprite(sfRenderWindow *window, sfSprite *sprite)
{
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f size = sfView_getSize(view);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = sfSprite_getPosition(sprite);
    sfVector2f origin = {center.x - size.x / 2, center.y - size.y / 2};
    sfVector2f pos_on_window = {origin.x + pos.x, origin.y + pos.y};

    sfSprite_setPosition(sprite, pos_on_window);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_setPosition(sprite, pos);
    return;
}

void view_dynamic_drawsprite(sfRenderWindow *window, sfSprite *sprite)
{
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f size = sfView_getSize(view);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f topleft = {center.x - (size.x / 2.), center.y - (size.y / 2.)};
    sfVector2f pos = sfSprite_getPosition(sprite);
    sfVector2f scale = sfSprite_getScale(sprite);
    sfVector2f pos_on_window = {
        .x = topleft.x + pos.x * size.x,
        .y = topleft.y + pos.y * size.y
    };
    sfVector2f new_scale = {scale.x * size.x / 1920, scale.y * size.y / 1080};

    sfSprite_setScale(sprite, new_scale);
    sfSprite_setPosition(sprite, pos_on_window);
    sfRenderWindow_drawSprite(window, sprite, NULL);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, scale);
    return;
}

sfBool view_is_in_sprite(sfRenderWindow *window,
    sfSprite *sprite, float x, float y)
{
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f size = sfView_getSize(view);
    sfVector2f pos = sfSprite_getPosition(sprite);
    sfVector2f scale = sfSprite_getScale(sprite);
    sfVector2f pos_on_window = {pos.x * size.x, pos.y * size.y};
    sfVector2f new_scale = {scale.x * size.x / 1920, scale.y * size.y / 1080};
    sfBool in = sfFalse;

    sfSprite_setScale(sprite, new_scale);
    sfSprite_setPosition(sprite, pos_on_window);
    in = is_in_sprite(sprite, x, y);
    sfSprite_setPosition(sprite, pos);
    sfSprite_setScale(sprite, scale);
    return in;
}
