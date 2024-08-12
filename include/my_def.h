/*
** EPITECH PROJECT, 2024
** myrpg [WSL: Ubuntu]
** File description:
** my_def.h
*/

#pragma once

#ifndef GAME_NAME
// Define the name of the video game.
    #define GAME_NAME "Graveyard Harvest"
#endif /* GAME_NAME */

#ifndef IS_PRINTABLE
// Define the printable characters.
    #define IS_PRINTABLE(x) (x >= 32 && x <= 126)
#endif /* IS_PRINTABLE */

#ifndef DEFAULT_FRAMERATE
// Define the maximum framerate value.
    #define DEFAULT_FRAMERATE 60
#endif /* DEFAULT_FRAMERATE */

#ifndef DATE_LEN
// Define the length of the date.
    #define DATE_LEN 20
#endif /* DATE_LEN */

#ifndef C_LIGHT_TEXT
// Define the color of the text.
    #define C_LIGHT_TEXT sfColor_fromRGB(230, 208, 167)
#endif /* C_LIGHT_TEXT */

#ifndef C_DARK_TEXT
// Define the color of the text.
    #define C_DARK_TEXT sfColor_fromRGB(166, 125, 104)
#endif /* C_DARK_TEXT */

#ifndef C_IN_TEXTBOX
// Define the color of the text box.
    #define C_IN_TEXTBOX sfColor_fromRGB(231, 208, 166)
#endif /* C_IN_TEXTBOX */

#ifndef C_OUT_TEXTBOX
// Define the color of the text box.
    #define C_OUT_TEXTBOX sfColor_fromRGB(242, 218, 189)
#endif /* C_OUT_TEXTBOX */

#ifndef MOVE_SPEED
    #define MOVE_SPEED 10
#endif /* MOVE_SPEED */

#ifndef ANIMATION_DURATION
    #define ANIMATION_DURATION 0.2
#endif /* ANIMATION_DURATION */

#ifndef DAY_DURATION
    #define DAY_DURATION 40
#endif /* DAY_DURATION */

#ifndef NIGHT_DURATION
    #define NIGHT_DURATION 20
#endif /* NIGHT_DURATION */

#ifndef DAY_PERIOD
    #define DAY_PERIOD (DAY_DURATION + NIGHT_DURATION)
#endif /* DAY_PERIOD */

#ifndef ATTACK_ANIMATION_DURATION
    #define ATTACK_ANIMATION_DURATION 0.1
#endif /* ATTACK_ANIMATION_DURATION */
