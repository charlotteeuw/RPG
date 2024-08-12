/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my_enum.h
*/

#pragma once

typedef enum e_scene {
    SCENE_TITLE,
    SCENE_SETTINGS,
    SCENE_SELECTION,
    SCENE_TUTO,
    SCENE_SPAWN,
    SCENE_OUTSIDE,
    SCENE_SHOP,
    SCENE_SHERIFF,
    SCENE_ROOM,
    SCENE_BOSS,
    SCENE_RESUME,
    SCENE_CREDITS,
    MAX_SCENES
} scene_t;

enum e_steps {
    INIT_WINDOW,
    INIT_DATA,
    INIT_PLAYER,
    INIT_UI,
    INIT_OUTSIDE,
    INIT_ROOMS,
    INIT_NPCS,
    INIT_GAME,
    LAST_INIT
};

enum e_button_state {
    BUTTON_NONE,
    BUTTON_HOVERED,
    BUTTON_PRESSED
};

enum e_sound {
    SOUND_CLICK,
    SOUND_SHOT,
    MAX_SOUNDS
};

enum e_slider {
    SLIDER_LEFT,
    SLIDER_RIGHT,
    SLIDER_HITBOX,
    MAX_SLIDERS
};

enum e_volume {
    VOLUME_SOUND,
    VOLUME_MUSIC,
    MAX_VOLUME
};

enum e_items {
    ITEM_POTION,
    ITEM_SWORD,
    ITEM_SEEDS,
    MAX_ITEMS
};

enum e_move {
    MOVING_ON,
    MOVING_OFF,
    SWITCH_MOVING
};

enum e_keybinds {
    BIND_UP,
    BIND_LEFT,
    BIND_DOWN,
    BIND_RIGHT,
    BIND_TOOL,
    BIND_INV,
    BIND_SPRINT,
    BIND_QUESTS,
    BIND_PAUSE,
    MAX_KEYBINDS
};
