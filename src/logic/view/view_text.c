/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** view_text.c
*/

#include <my.h>

void view_drawtext(sfRenderWindow *window, sfText *text)
{
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f size = sfView_getSize(view);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = sfText_getPosition(text);
    sfVector2f origin = {center.x - size.x / 2, center.y - size.y / 2};
    sfVector2f pos_on_window = {origin.x + pos.x, origin.y + pos.y};

    sfText_setPosition(text, pos_on_window);
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setPosition(text, pos);
    return;
}

void view_dynamic_drawtext(sfRenderWindow *window, sfText *text)
{
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f size = sfView_getSize(view);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f topleft = {center.x - (size.x / 2.), center.y - (size.y / 2.)};
    sfVector2f pos = sfText_getPosition(text);
    sfVector2f scale = sfText_getScale(text);
    sfVector2f pos_on_window = {
        .x = topleft.x + pos.x * size.x,
        .y = topleft.y + pos.y * size.y
    };
    sfVector2f new_scale = {scale.x * size.x / 1920, scale.y * size.y / 1080};

    sfText_setScale(text, new_scale);
    sfText_setPosition(text, pos_on_window);
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setPosition(text, pos);
    sfText_setScale(text, scale);
    return;
}

void view_center_drawtext(sfRenderWindow *window, sfText *text)
{
    const sfView *view = sfRenderWindow_getView(window);
    sfVector2f center = sfView_getCenter(view);
    sfVector2f pos = sfText_getPosition(text);
    sfVector2f pos_on_window = {center.x + pos.x, center.y + pos.y};

    sfText_setPosition(text, pos_on_window);
    sfRenderWindow_drawText(window, text, NULL);
    sfText_setPosition(text, pos);
    return;
}
