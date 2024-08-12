/*
** EPITECH PROJECT, 2024
** MyRPG
** File description:
** controls.c
*/

#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "my.h"

const char *config_dir = ".config";

const char *keys_name[sfKeyCount] = {
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Escape",
    "LControl",
    "LShift",
    "LAlt",
    "LSystem",
    "RControl",
    "RShift",
    "RAlt",
    "RSystem",
    "Menu",
    "LBracket",
    "RBracket",
    "Semicolon",
    "Comma",
    "Period",
    "Quote",
    "Slash",
    "Backslash",
    "Tilde",
    "Equal",
    "Hyphen",
    "Space",
    "Enter",
    "Backspace",
    "Tab",
    "PageUp",
    "PageDown",
    "End",
    "Home",
    "Insert",
    "Delete",
    "Add",
    "Subtract",
    "Multiply",
    "Divide",
    "Left",
    "Right",
    "Up",
    "Down",
    "Numpad0",
    "Numpad1",
    "Numpad2",
    "Numpad3",
    "Numpad4",
    "Numpad5",
    "Numpad6",
    "Numpad7",
    "Numpad8",
    "Numpad9",
    "F1",
    "F2",
    "F3",
    "F4",
    "F5",
    "F6",
    "F7",
    "F8",
    "F9",
    "F10",
    "F11",
    "F12",
    "F13",
    "F14",
    "F15",
    "Pause"
};

static void set_control(unsigned short *controls, char *control, char *bind)
{
    int key_control = atoi(control);
    int key_bind = atoi(bind);

    if (key_control >= 0 && key_control <= 8) {
        if (key_bind >= 0 && key_bind <= 100) {
            controls[key_control] = key_bind;
        }
    }
}

static void retrieve_configuration(unsigned short *keybinds, char **lines)
{
    char **line = NULL;

    for (size_t i = 0; lines[i] != NULL; i++) {
        line = my_splitstr(lines[i], ":");
        if (line != NULL && line[0] != NULL && line[1] != NULL) {
            set_control(keybinds, line[0], line[1]);
            my_freearray(line);
        }
    }
}

static unsigned short *initialize_keybinds(void)
{
    unsigned short *keybinds = malloc(sizeof(unsigned short) * MAX_KEYBINDS);

    if (keybinds != NULL) {
        keybinds[BIND_UP] = sfKeyZ;
        keybinds[BIND_LEFT] = sfKeyQ;
        keybinds[BIND_DOWN] = sfKeyS;
        keybinds[BIND_RIGHT] = sfKeyD;
        keybinds[BIND_TOOL] = sfKeyE;
        keybinds[BIND_INV] = sfKeyI;
        keybinds[BIND_SPRINT] = sfKeyLShift;
        keybinds[BIND_QUESTS] = sfKeyF;
        keybinds[BIND_PAUSE] = sfKeyEscape;
    }
    return keybinds;
}

unsigned short *create_keybinds(void)
{
    unsigned short *keybinds = initialize_keybinds();
    char *content = NULL;
    char **lines = NULL;

    if (keybinds != NULL) {
        content = my_open(".config/keybinds");
        if (!content) {
            return keybinds;
        }
        lines = my_splitstr(content, "\n");
        if (lines != NULL) {
            retrieve_configuration(keybinds, lines);
            my_freearray(lines);
        }
        free(content);
    }
    return keybinds;
}

void save_keybinds(unsigned short *keybinds)
{
    char *str = ".config/keybinds";
    struct stat st = {0};
    int fd = 0;

    if (stat(config_dir, &st) != 0) {
        my_puts(STDOUT_FILENO, "Creating config directory...\n");
        mkdir(config_dir, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
    }
    fd = open(str, O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd != -1) {
        for (enum e_keybinds i = 0; i < MAX_KEYBINDS; i++) {
            dprintf(fd, "%d:%d\n", i, keybinds[i]);
        }
        close(fd);
    } else {
        my_puts(STDOUT_FILENO, "Error while saving the game\n");
    }
}
