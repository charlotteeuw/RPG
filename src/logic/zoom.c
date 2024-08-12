/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** zoom.c
*/

#include <my.h>

void analyse_zoom_events(sfRenderWindow *window, sfEvent *event)
{
    sfView *view;
    sfVector2f size;

    if (event->type != sfEvtMouseWheelScrolled ||
        event->mouseWheelScroll.wheel != sfMouseVerticalWheel) {
        return;
    }
    view = sfView_copy(sfRenderWindow_getView(window));
    size = sfView_getSize(view);
    size.x = size.x * (1 + 0.1 * event->mouseWheelScroll.delta);
    if (960 < size.x && size.x < 3840) {
        sfView_zoom(view, 1 + 0.1 * event->mouseWheelScroll.delta);
        sfRenderWindow_setView(window, view);
    }
    sfView_destroy(view);
}
