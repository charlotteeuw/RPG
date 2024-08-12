/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** windows.c
*/

#include <sys/stat.h>
#include <stdlib.h>
#include "my_msg.h"
#include "my_def.h"
#include <stdio.h>
#include "my.h"

const char *screenshot_dir = "./screenshots";

static void save_screenshot(sfImage *screenshot)
{
    char *date = create_date();
    struct stat st = {0};
    char str[50] = {0};

    if (stat(screenshot_dir, &st) != 0) {
        my_puts(STDOUT_FILENO, "Creating screenshots directory...\n");
        mkdir(screenshot_dir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    if (date != NULL) {
        snprintf(str, 50, "%s/screenshot_%s.png", screenshot_dir, date);
        sfImage_saveToFile(screenshot, str);
        free(date);
    }
}

void take_screenshot(sfRenderWindow* window, sound_t *sound)
{
    sfTexture *texture = sfTexture_create(1920, 1080);
    sfImage* screenshot = NULL;

    if (texture != NULL) {
        sfTexture_updateFromRenderWindow(texture, window, 0, 0);
        screenshot = sfTexture_copyToImage(texture);
        if (!screenshot) {
            sfTexture_destroy(texture);
            return;
        }
        save_screenshot(screenshot);
        if (sound->play) {
            sfSound_play(sound->play);
        }
        sfImage_destroy(screenshot);
        sfTexture_destroy(texture);
    }
}

static void set_window_icon(sfRenderWindow *window)
{
    sfImage *image = sfImage_createFromFile("./assets/images/icon.png");
    const sfUint8 *pixels = NULL;
    sfVector2u size = {0, 0};

    if (image != NULL) {
        pixels = sfImage_getPixelsPtr(image);
        if (pixels != NULL) {
            size = sfImage_getSize(image);
            sfRenderWindow_setIcon(window, size.x, size.y, pixels);
        }
        sfImage_destroy(image);
    }
}

sfRenderWindow *create_window(sfUint8 style,
    unsigned int width, unsigned int height, unsigned int framerate)
{
    sfVideoMode mode = {width, height, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode,
        GAME_NAME, style, NULL);
    sfVector2i position = {0, 0};

    if (window != NULL) {
        sfRenderWindow_setFramerateLimit(window, framerate);
        sfRenderWindow_setMouseCursorVisible(window, sfFalse);
        sfRenderWindow_setPosition(window, position);
        set_window_icon(window);
    } else {
        my_puts(STDERR_FILENO, E_CREATW);
    }
    return (window);
}
