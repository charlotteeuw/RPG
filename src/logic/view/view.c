/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** view.c
*/

#include <my.h>

void rw_set_view_position(sfRenderWindow *window, sfVector2f position)
{
    sfView *view = sfView_copy(sfRenderWindow_getView(window));

    sfView_setCenter(view, position);
    sfRenderWindow_setView(window, view);
    sfView_destroy(view);
}

void rw_move_view(sfRenderWindow *window, sfVector2f offset)
{
    sfView *view = sfView_copy(sfRenderWindow_getView(window));

    sfView_move(view, offset);
    sfRenderWindow_setView(window, view);
    sfView_destroy(view);
}
