/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_nbrlen.c
*/

int my_nbrlen(int nbr)
{
    int len = 0;

    if (nbr != 0) {
        if (nbr < 0) {
            len = 1;
            nbr = -nbr;
        }
        while (nbr > 0) {
            nbr /= 10;
            len++;
        }
    } else {
        len = 1;
    }
    return len;
}
