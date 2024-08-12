/*
** EPITECH PROJECT, 2024
** myrpg
** File description:
** my.h
*/

#pragma once

/* Include library dependencies */

#include <SFML/Graphics.h>
#include <SFML/Config.h>
#include <SFML/Audio.h>

#include <unistd.h>
#include <stdbool.h>

/* Include my dependencies */

#include "my_enum.h"

/* Array declaration */

extern const sfIntRect shapes[3];

extern const char *keys_name[sfKeyCount];

/* Types and structures declaration */

typedef struct s_sprite {
    sfTexture *texture;
    sfSprite *sprite;
} sprite_t;

typedef struct s_progress {
    sfRectangleShape *foreground;
    sfRectangleShape *background;
} progress_t;

typedef struct s_sound {
    sfSoundBuffer *buffer;
    sfSound *play;
} sound_t;

typedef struct list_s {
    void *data;
    struct list_s *next;
} list_t;

typedef struct s_textbox {
    sfRectangleShape *frame;
    sfBool active;
    sfText *text;
} textbox_t;

typedef struct s_pause {
    sfText *text;
    sprite_t *plate;
    list_t *buttons;
    bool is_open;
} pause_t;

typedef struct s_title {
    list_t *buttons;
    sprite_t *logo;
    sfMusic *music;
} title_t;

typedef struct s_rain {
    sfVector2f position;
    float speed;
    sprite_t *sprite;
} rain_t;

typedef struct s_snow {
    sfVector2f position;
    float speed;
    sprite_t *sprite;
} snow_t;

typedef struct s_quests {
    sprite_t *img;
    sprite_t *unchecked;
    sprite_t *checked;
    bool is_open;
    sfText *quests;
    sfText *quest1;
    sfText *quest2;
    sfText *quest3;
    sfText *quest4;
    sfText *quest5;
    sfText *quest6;
    sfText *stats;
    sfText *experience;
    sfText *level;
    sfText *life;
    sfText *damage;
    sfText *speed;
    sfText *xp;
    sfText *lvl;
    sfText *health;
    sfText *dmg;
    sfText *spd;
    int first_quest;
    int second_quest;
    int third_quest;
    int fourth_quest;
    int fifth_quest;
    int final_quest;
    float fast;
} quests_t;

typedef struct s_slider {
    sfRectangleShape *bars[MAX_SLIDERS];
    sfCircleShape *cursor;
    sfVector2f position;
    sfVector2f size;
    sfBool active;
} slider_t;

typedef struct s_settings {
    void *keybinds[MAX_KEYBINDS];
    unsigned int framerate;
    bool fullscreen;
    sprite_t *plate;
    slider_t *sound;
    slider_t *music;
    list_t *buttons;
    list_t *texts;
} settings_t;

typedef struct s_item {
    void (*action)(quests_t *);
    unsigned int quantity;
    sfText *quantity_text;
    sprite_t *img;
    bool is_hover;
    sfText *name;
} item_t;

typedef struct s_inventory {
    item_t **items;
    sprite_t *img;
    bool is_open;
} inventory_t;

typedef struct s_player {
    bool male;
    bool moving;
    bool attacking;
    char *name;
    int health;
    sfClock *clock;
    sprite_t *sprite;
    sprite_t *attack;
    sprite_t *health_bar;
    inventory_t *inventory;
    quests_t *quests;
    pause_t *pause;
    sfVector2f pos;
    int level;
    int experience;
    int damage;
} player_t;

typedef struct s_selection {
    sfRectangleShape *rect;
    sprite_t *background;
    sprite_t *woman_sprite;
    sprite_t *man_sprite;
    sprite_t *woman_logo;
    sprite_t *man_logo;
    list_t *buttons;
    sprite_t *plate;
    sfText *name;
    textbox_t *textbox;
} selection_t;

typedef struct s_resume {
    void *back;
    list_t *saves;
    sprite_t *plate;
    sfText *title;
} resume_t;

typedef struct s_tuto {
    sprite_t *bg;
    sfImage *collision;
    sprite_t *player;
    sprite_t *dialogue;
    sprite_t *icon;
    sprite_t *arrow;
    sfText *text;
} tuto_t;

typedef struct s_shop {
    sprite_t *bg;
    sfImage *collision;
    sprite_t *npc;
    sprite_t *dialogue;
    sprite_t *icon;
    sfIntRect frame;
    sfText *text;
    int is_dialogue;
    int passed;
} shop_t;

typedef struct s_sheriff {
    sprite_t *bg;
    sfImage *collision;
    sprite_t *npc;
    sprite_t *dialogue;
    sprite_t *icon;
    sfText *text;
    int is_dialogue;
    int passed;
} sheriff_t;

typedef struct s_spawn {
    sprite_t *bedroom;
    sfImage *collision;
    sprite_t *icon;
    sprite_t *dialogue;
    sfText *text;
    int is_dialogue;
    int passed;
} spawn_t;

typedef struct s_outside {
    sprite_t *bg;
    sfImage *collision;
    sprite_t *up_bg;
    sprite_t *night_bg;
    sprite_t *sunset_bg;
    sprite_t *dialogue;
    sprite_t *icon;
    sfText *text;
    sfText *night1;
    sfText *final_text;
    sfVector2f dialogue_pos;
    int is_dialogue;
    int night;
    int passed;
    int passed_final;
    int passed_end;
    int passed_night;
} outside_t;

typedef struct s_room {
    sprite_t *bg;
    sfImage *collision;
    sprite_t *npc;
    sprite_t *icon;
    sprite_t *dialogue;
    sfText *text;
    int is_dialogue;
    int passed;
} room_t;

typedef struct s_npc {
    sprite_t *sprite;
    sfVector2f position;
    sfIntRect frame;
} npc_t;

typedef struct s_zombie {
    sprite_t *sprite;
    sfVector2f position;
    sfIntRect frame;
    sfFloatRect bounds;
    sfVector2f pos;
    float last;
    int health;
} zombie_t;

typedef struct s_boss {
    sprite_t *bg;
    sfImage *collision;
    sprite_t *dialogue;
    sprite_t *icon;
    sfText *text;
    zombie_t *mega;
    int is_dialogue;
    int passed;
    int fight;
} boss_t;

typedef struct s_fade {
    sfRectangleShape *img;
    bool active;
} fade_t;

typedef struct s_game {
    sound_t *sounds[MAX_SOUNDS];
    sfBool framerate_displayed;
    float volumes[MAX_VOLUME];
    sfRenderWindow *window;
    sfClock *clock;
    settings_t *settings;
    sfText *framerate;
    sprite_t *cursor;
    sfVector2f mouse;
    title_t *title;
    scene_t scene;
    sprite_t *bg;
    sprite_t *dialogue;
    selection_t *selection;
    tuto_t *tuto;
    player_t *player;
    spawn_t *spawn;
    unsigned short *keybinds;
    outside_t *outside;
    sprite_t *cat;
    int cat_is_dead;
    int day;
    bool is_day;
    int current_time_in_day;
    sfText *day_text;
    sfText *level;
    shop_t *shop;
    sheriff_t *sheriff;
    room_t *room;
    npc_t **npcs;
    zombie_t **zombies;
    boss_t *boss;
    bool help_displayed;
    sfText *help;
    resume_t *resume;
    rain_t *rain;
    snow_t *snow;
    fade_t *fade;
} game_t;

typedef struct s_button {
    enum e_button_state state;
    void (*action)(game_t *, struct s_button *);
    sprite_t *frame;
    sfText *text;
} button_t;

/* Functions prototypes */

/**
* @brief Free a NULL terminated array of pointers
*
* @param ptr The array to free
*/
void my_freearray(void *ptr);

/**
* @brief Converts an integer to a string
*
* @param nbr The integer to be converted
*
* @return A pointer to the allocated string containing the converted integer
*/
char *my_itoa(int nbr);

/**
* @brief Computes the number of digits in an integer
*
* @param nbr The integer whose number of digits is to be calculated
*
* @return The number of digits in the integer
*/
int my_nbrlen(int nbr);

/**
 * @brief Open a file and returns its content
 *
 * @param filepath The path to the file
 *
 * @return The content of the file
*/
char *my_open(char const *filepath);

/**
* @brief Writes a string to a file descriptor
*
* @param fd The file descriptor to write to
* @param str Pointer to the string to be written
*
* @return The number of bytes written
*/
size_t my_puts(int fd, char const *str);

/**
* @brief Concatenates two strings and returns the result
*
* @param dst Pointer to the destination string where 'src' will be concatenated
* @param src Pointer to the source string to be concatenated
*
* @return A pointer to the concatenated string
*/
char *my_strcat(char *restrict dst, char const *restrict src);

/**
* @brief The function copy the string pointed to by src, into a
* string at the buffer pointed to by dst. Make sure that the dst
* have enough place to contain the src content
*
* @param dst The string into which we copy
* @param src The string to copy
*/
char *my_strcpy(char *restrict dst, char const *restrict src);

/**
* @brief The function returns a pointer to a new string which is
* a duplicate of the given string
*
* @param str The string to duplicate
*
* @return A pointer to the duplicated string
*/
char *my_strdup(char const *str);

/**
* @brief Computes the length of a string
*
* @param str Pointer to the string whose length is to be calculated
*
* @return Length of the string
*/
size_t my_strlen(char const *str);

/**
* @brief Creates a new window with the specified style, width, and height
*
* @param style The style of the window (e.g., sfFullscreen, sfClose)
* @param width The width of the window
* @param height The height of the window
* @param framerate The framerate of the window
*
* @return A pointer to the newly created window
*/
sfRenderWindow *create_window(sfUint8 style,
    unsigned int width, unsigned int height, unsigned int framerate);

/**
* @brief Takes a screenshot of the window and saves it to a file
*
* @param window Pointer to the window to take a screenshot of
* @param sound Pointer to the sound to play when taking a screenshot
*/
void take_screenshot(sfRenderWindow* window, sound_t *sound);

/**
* @brief Analyse events of the window
*
* @param game Pointer to the game instance
* @param event The event to analyse
*/
void analyse_events(game_t *game, sfEvent *event);

/**
* @brief Analyzes events specific to the title screen
*
* @param game Pointer to the game structure
* @param event Pointer to the event to analyze
*/
void analyse_title_events(game_t *game, sfEvent *event);

/**
* @brief Analyzes events specific to a button
*
* @param game Pointer to the game structure
* @param event Pointer to the event to analyze
* @param button Pointer to the button to analyze events for
*/
void analyse_button_events(game_t *game, sfEvent *event, button_t *button);

/**
* @brief Centers a sprite by setting its origin to the center of its bounds
*
* @param sprite Pointer to the SFML sprite to be centered
*/
void center_sprite(sfSprite *sprite);

/**
* @brief Creates a new sprite from the specified file
*
* @param file Path to the image file for the sprite
*
* @return A pointer to the newly created sprite, or NULL if creation fails
*/
sprite_t *create_sprite(char const *file);

/**
* @brief Destroys a sprite and frees allocated memory
*
* @param sprite Pointer to the sprite structure to be destroyed
*/
void destroy_sprite(sprite_t *sprite);

/**
* @brief Renders the main menu on the specified render window
*
* @param game A pointer to the game structure
*/
void render_title(game_t *game);

/**
* @brief Creates a main menu with default settings
*
* @return A pointer to the newly created main menu
*/
title_t *create_title(void);

/**
* @brief Destroys the main menu and frees allocated memory
*
* @param title Pointer to the main menu structure to be destroyed
*/
void destroy_title(title_t *title);

/**
* @brief Creates a title screen with default settings
*
* @return A pointer to the newly created title screen
*/
title_t *create_title(void);

/**
* @brief Switches the game scene to the title screen
*
* @param game Pointer to the game structure
* @param button Pointer to the button that triggered the switch
*/
void switch_to_title(game_t *game, button_t *button);

/**
* @brief Creates and initializes the game
*
* @param game A pointer to the game to be created
*
* @return Whether the game was created successfully
*/
bool create_game(game_t *game);

/**
* @brief Destroys a game instance and frees allocated memory
*
* @param game Pointer to the game instance to be destroyed
*/
void destroy_game(game_t *game);

/**
* @brief Renders the current game scene on the specified render window
*
* @param game Pointer to the game instance
*/
void render_game(game_t *game);

/**
* @brief Creates a string representing the current date and time
*
* @return str The string where the date will be stored
*/
char *create_date(void);

/**
* @brief Checks if a point is within the bounds of a sprite
*
* @param sprite Pointer to the sprite to check
* @param x X-coordinate of the point to be checked
* @param y Y-coordinate of the point to be checked
*
* @return Whether the point is within the bounds
*/
sfBool is_in_sprite(sfSprite const *sprite, float x, float y);

/**
* @brief Checks if a point is within the bounds of a rectangle
*
* @param rectangle Pointer to the rectangle to check
* @param x X-coordinate of the point to be checked
* @param y Y-coordinate of the point to be checked
*
* @return Whether the point is within the bounds
*/
sfBool is_in_rect(sfRectangleShape const *rectangle, float x, float y);

/**
* @brief Checks if a point is within the bounds of a circle
*
* @param circle Pointer to the circle to check
* @param x X-coordinate of the point to be checked
* @param y Y-coordinate of the point to be checked
*
* @return Whether the point is within the bounds
*/
sfBool is_in_circle(sfCircleShape const *circle, float x, float y);

/**
* @brief Appends data to the beginning of a linked list
*
* @param head Pointer to the pointer to the head of the linked list
* @param data Pointer to the data to be appended
*/
void append_to_list(list_t **head, void *data);

/**
* @brief Destroys a linked list and frees allocated memory
*
* @param list Pointer to the head of the linked list to be destroyed
* @param destroy Pointer to the function used to destroy each data element
*/
void destroy_list(list_t *list, void (*destroy)(void *));

/**
* @brief Creates a new SFML music object from the specified file
*
* @param file Path to the audio file
*
* @return A pointer to the newly created music
*/
sfMusic *create_music(char *file);

/**
* @brief Centers a text at the specified position
*
* @param text Pointer to the text to be centered
* @param position Position at which to center the text
*/
void set_text_position(sfText *text, sfVector2f position);

/**
 * @brief Set the origin of a text to its center
 *
 * @param text Pointer to the text to be centered
*/
void center_text_origin(sfText *text);

/**
* @brief Creates a new SFML text object with the specified string
*
* @param str The string content of the text
* @param color The color of the text
* @param size The size of the text
*
* @return A pointer to the newly created text
*/
sfText *create_text(char const *str, sfColor color, unsigned int size);

/**
 * @brief Destroys a text and frees allocated memory
 *
 * @param ptr Pointer to the text to be destroyed
*/
void destroy_text(void *ptr);

/**
* @brief Renders a button on the specified render window
*
* @param window Pointer to the render window
* @param button Pointer to the button structure to be rendered
*/
void render_button(sfRenderWindow *window, button_t *button);

/**
* @brief Destroys a button and frees allocated memory
*
* @param button Pointer to the button structure to be destroyed
*/
void destroy_button(void *button);

/**
* @brief Creates a new button with the specified action, text, and image
*
* @param text The text to be displayed on the button
* @param position The position vector of the sprite
* @param scale The scale vector of the sprite
* @param action The action to be executed when the button is clicked
*
* @return A pointer to the newly created button
*/
button_t *create_button(char const *text, sfVector2f position,
    sfVector2f scale, void (*action)(game_t *, struct s_button *));

/**
* @brief Creates a sound from a file
*
* @param file Path to the sound file
*
* @return A pointer to the newly created sound
*/
sound_t *create_sound(char const *file);

/**
* @brief Destroys a sound and its associated resources
*
* @param sound Pointer to the sound structure to be destroyed
*/
void destroy_sound(sound_t *sound);

/**
* @brief Handles the exit action for the game
*
* @param game Pointer to the game structure
* @param button Pointer to the button that triggered the action
*/
void action_exit(game_t *game, button_t *button);

/**
* @brief Creates a textbox with the given position, size, and font size
*
* @param position The position of the textbox
* @param size The size of the textbox
* @param font_size The font size of the text inside the textbox
*
* @return A pointer to the created textbox
*/
textbox_t *create_textbox(sfVector2f position,
    sfVector2f size, unsigned int font_size);

/**
* @brief Renders the given textbox on the specified render window
*
* @param window The render window to render the textbox onto
* @param textbox A pointer to the textbox to be rendered
*/
void render_textbox(sfRenderWindow *window, textbox_t *textbox);

/**
* @brief Analyzes the specified event for interactions with the given textbox
*
* @param game A pointer to the game structure containing relevant data
* @param event A pointer to the event to be analyzed
* @param textbox A pointer to the textbox to be interacted with
*
* @return Whether the text was updated
*/
bool analyse_textbox_events(game_t *game, sfEvent *event, textbox_t *textbox);

/**
* @brief Centers a rectangle shape based on specified axes
*
* @param rect Pointer to the rectangle shape to be centered
* @param x Whether to center the rectangle shape along the x-axis
* @param y Whether to center the rectangle shape along the y-axis
*/
void center_rect(sfRectangleShape *rect, bool x, bool y);

/**
* @brief Creates a rectangle shape with specified properties
*
* @param position The position of the rectangle shape
* @param size The size of the rectangle shape
* @param color The color of the rectangle shape
*
* @return A pointer to the created rectangle shape
*/
sfRectangleShape *create_rect(sfVector2f position,
    sfVector2f size, sfColor color);

/**
* @brief Creates a settings structure
*
* @return A pointer to the created settings
*/
settings_t *create_settings(void);

/**
* @brief Renders the settings screen
*
* @param game Pointer to the game structure
*/
void render_settings(game_t *game);

/**
* @brief Analyzes events for the settings screen
*
* @param game Pointer to the game structure
* @param event Pointer to the event to be analyzed
*/
void analyse_settings_events(game_t *game, sfEvent *event);

/**
* @brief Destroys a settings structure
*
* @param settings Pointer to the settings to be destroyed
*/
void destroy_settings(settings_t *settings);

/**
* @brief Switches the game scene to the settings screen
*
* @param game Pointer to the game structure
* @param button Pointer to the button that triggered the switch
*/
void switch_to_settings(game_t *game, button_t *button);

/**
* @brief Creates a slider with specified properties
*
* This function creates a slider with the specified position, size, and color.
* It also creates a cursor for the slider with adjusted color properties.
*
* @param position The position of the slider
* @param size The size of the slider
*
* @return A pointer to the created slider
*/
slider_t *create_slider(sfVector2f position, sfVector2f size);

/**
* @brief Destroys a slider and its associated resources
*
* @param slider Pointer to the slider to be destroyed
*/
void destroy_slider(slider_t *slider);

/**
* @brief Analyzes mouse events for a slider
*
* @param slider Pointer to the slider to be analyzed
* @param mouse The current position of the mouse cursor
* @param value Pointer to the value to be updated based on the slider position
*/
void analyse_slider_events(slider_t *slider, sfVector2f mouse, float *value);

/**
* @brief Renders a slider on a render window
*
* @param window Pointer to the render window
* @param slider Pointer to the slider to be rendered
*/
void render_slider(sfRenderWindow *window, slider_t *slider);

/**
* @brief Updates the volumes of sounds and music
*
* @param game The game containing volume settings and audio components
*/
void update_volumes(game_t *game);

/**
* @brief Whether to display the fps
*
* @param game The game containing the fps text
* @param button The button that triggered the action
*/
void switch_framerate(game_t *game, button_t *button);

/**
* @brief Returns the elapsed time in seconds since the clock has started, then
* restarts the clock
*
* @param clock Pointer to the clock to get the elapsed time from
*
* @return The elapsed time in seconds
*/
float restart_clock(sfClock *clock);

/**
* @brief Sets the framerate limit of the window to 30
*
* @param game Pointer to the game structure
* @param button Pointer to the button that triggered the action
*/
void set_framerate_30(game_t *game, button_t *button);

/**
* @brief Sets the framerate limit of the window to 60
*
* @param game Pointer to the game structure
* @param button Pointer to the button that triggered the action
*/
void set_framerate_60(game_t *game, button_t *button);

/**
* @brief UnSets the framerate limit of the window
*
* @param game Pointer to the game structure
* @param button Pointer to the button that triggered the action
*/
void set_framerate_max(game_t *game, button_t *button);

/**
* @brief Resets the button to its default state
*
* @param button Pointer to the button to be reset
*/
void reset_button(button_t *button);

/**
* @brief Changes the scene to selection screen
*
* @param title Pointer to the game and button structure
*/
void switch_selection(game_t *game, __attribute__((unused)) button_t *button);

/**
* @brief Analyses the events of the selection screen scene
*
* @param title Pointer to the game and event structure
*/
void analyse_selection_events(game_t *game, sfEvent *event);
selection_t *create_selection(void);

/**
* @brief Renders the selection screen scene
*
* @param game A pointer to the game structure
*/
void render_selection(game_t *game);

/**
* @brief Destroys the selection menu and frees allocated memory
*
* @param title Pointer to the selection screen structure to be destroyed
*/
void destroy_selection(selection_t *scene);

/**
* @brief Function to create a rectangle
*
* @param title Position of the rectangle
*/
sfRectangleShape *create_rectangle(sfVector2f position);

/**
* @brief Creates the scene of the tutorial
*
* @param title Void
*/
tuto_t *create_tuto(void);

/**
* @brief Renders the tutorial scene
*
* @param game A pointer to the game structure
*/
void render_tuto(game_t *game);

/**
* @brief Destroys the tutorial scene and frees allocated memory
*
* @param title Pointer to the tutorial screen structure to be destroyed
*/
void destroy_tuto(tuto_t *tuto);

/**
* @brief Switches the scene to the tutorial scene
*
* @param title Pointer to the game structure and button structure
*/
void switch_to_tuto(game_t *game);

/**
* @brief Analyses the events of the tutorial scene
*
* @param title Pointer to the game and event structure
*/
void analyse_tuto_events(game_t *game, sfEvent *event);

/**
* @brief Animates the player
*
* @param game Pointer to the game structure
*/
void animate_player(game_t *game);

/**
 * @brief Moves the player
 *
 * @param game A pointer to the game structure
 *
 * @return The movement vector of the player
*/
sfVector2f move_player(game_t *game);

/**
 * @brief Manages the movement of the entities
 *
 * @param game A pointer to the game structure
*/
void manage_movement(game_t *game);

/**
* @brief Sets the next paragraph of the text
*
* @param text Pointer to the text
* @param file Filename, however call with NULL if you've already called this
*/
sfText *next_paragraph(sfText *text, char *file, char *name);

/**
* @brief Creates a sfText that will contain the first text of the file
*
* @param title Filename
*/
sfText *create_dialogue_text(char *file, char *name);

/**
* @brief Prints the dialogue and changes the text by splitting on '@'
*
* @param title Pointer to the game structure, event, and position of the text
*/
sfText *handle_dialogue(game_t *game, sfEvent *event,
    sfVector2f position, sfText *text);

/**
* @brief Splits a string into substrings using a delimiter
*
* @param str Pointer to the string to be split
* @param delim Pointer to the delimiter string
*
* @return An array of pointers to the substrings
*/
char **my_splitstr(char const *str, char const *delim);

/**
 * @brief Change de mode of the window to fullscreen
 *
 * @param game Pointer to the game structure
 * @param button Pointer to the button that triggered the action
*/
void set_fullscreen(game_t *game, __attribute__((unused)) button_t *button);

/**
 * @brief Change de mode of the window to windowed
 *
 * @param game Pointer to the game structure
 * @param button Pointer to the button that triggered the action
*/
void set_windowed(game_t *game, __attribute__((unused)) button_t *button);

/**
* @brief Creates the scene of the spawn room
*/
spawn_t *create_spawn(void);

/**
* @brief Renders the spawn scene
*
* @param game A pointer to the game structure
*/
void render_spawn(game_t *game);

/**
 * @brief Analyses the events of the spawn scene
 *
 * @param game A pointer to the game structure
 * @param event A pointer to the event to be analysed
*/
void analyse_spawn_events(game_t *game, sfEvent *event);

/**
 * @brief Switches the scene to the spawn room
 *
 * @param game Pointer to the game structure
*/
void switch_to_spawn(game_t *game);

/**
* @brief Switches the scene to the game scene
*
* @param title Pointer to the game
*/
void start_game(game_t *game, sfVector2f pos);

/**
* @brief Analyses the events of the main game scene
*
* @param title Pointer to the game struct, and event
*/
void analyse_game_events(game_t *game, __attribute__((unused)) sfEvent *event);

/**
 * @brief Render the outside scene
 *
 * @param game A pointer to the game structure
*/
void render_outside(game_t *game);

/**
 * @brief Creates the keybinds from the configuration file
 *
 * @return The structure containing the keybinds
*/
unsigned short *create_keybinds(void);

/**
* @brief Creates the main game
*
* @return The structure containing that structure
*/
outside_t *create_outside(void);

void update_cat_position(game_t *game, sfVector2f move);

/**
* @brief Sets the view to where the player is
*
* @param title window and player position
*/
void setposition_view(sfRenderWindow *window, sfVector2f pos);

/**
* @brief Function to draw a dialogue
*
* @param title sfText corresponding to the dialogue and window
*/
void draw_dialogue(sfText *text, sfRenderWindow *window);

/**
* @brief Sets the scene to the shop scene
*
* @param game A pointer to the game structure
*/
void switch_to_shop(game_t *game);

/**
* @brief Creates the shop scene
*
* @param title void
*/
shop_t *create_shop(void);

/**
* @brief Render the shop scene
*
* @param game A pointer to the game structure
*/
void render_shop(game_t *game);

/**
* @brief Analyses the events related to the shop scene
*
* @param title game and event
*/
void analyse_shop_events(game_t *game, __attribute__((unused)) sfEvent *event);

/**
* @brief Sets the scene to the sheriff scene
*
* @param gale A pointer to the game scene
*/
void switch_to_sheriff(game_t *game);

/**
* @brief Creates the sheriff scene
*
* @param title Void
*/
sheriff_t *create_sheriff(void);

/**
* @brief Render the game scene
*
* @param game A pointer to the game structure
*/
void render_sheriff(game_t *game);

/**
* @brief Analyses the events related to the sheriff scene
*
* @param title game and event
*/
void analyse_sheriff_events(game_t *game, sfEvent *event);

/**
* @brief Destroys the outside scene
*
* @param outside Outside structure
*/
void destroy_outside(outside_t *outside);

/**
* @brief Destroys the sheriff scene
*
* @param sheriff Sheriff structure
*/
void destroy_sheriff(sheriff_t *sheriff);

/**
* @brief Destroys the shop scene
*
* @param shop Shop structure
*/
void destroy_shop(shop_t *shop);

/**
* @brief Sets the scene to the room scene
*
* @param game A pointer to the game structure
*/
void switch_to_room(game_t *game);

/**
* @brief Creates he room scene
*
* @param void Void
*/
room_t *create_room(void);

/**
* @brief Destroys the room scene
*
* @param room Room structure
*/
void destroy_room(room_t *room);

/**
 * @brief Render the room scene
 *
 * @param game A pointer to the game structure
*/
void render_room(game_t *game);

/**
 * @brief Analyses the room scene events
 *
 * @param game A pointer to the game structure
 * @param event Event to analyse
*/
void analyse_room_events(game_t *game, sfEvent *event);

/**
 * @brief Creates the array of NPCS
 *
 * @param file file to open
 * @param position position to place the NPC
*/
npc_t *create_npc(const char *file, sfVector2f position);

/**
 * @brief Moves the NPC
 *
 * @param npc Array of NPCS
*/
void move_npc(npc_t *npc);

/**
 * @brief Renders the NPCS
 *
 * @param window Window to draw on
 * @param npc Array of NPCS
*/
void render_npcs(sfRenderWindow *window, npc_t **npcs);

/**
* @brief Zoom or dezoom on the map with the scroll wheel
*
* @param window Window to zoom or dezoom on
* @param event Event to analyse
*/
void analyse_zoom_events(sfRenderWindow *window, sfEvent *event);

/**
 * @brief Creates the zombies
 *
 * @param void vid
*/
zombie_t *create_zombie(void);

/**
 * @brief Moves the zombies
 *
 * @param game Game structure
 * @param zombies Array of zombiess
*/
void move_zombie(game_t *game, zombie_t **zombies);

/**
 * @brief Analyses the collisions of the zombies
 *
 * @param game Game structure
*/
void analyse_zombie_collisions(game_t *game);

/**
 * @brief Create a progress bar element
 *
 * @param position Position of the progress bar
 * @param size Size of the progress bar
 *
 * @return The progress bar element
*/
progress_t *create_progress(sfVector2f position, sfVector2f size);

/**
 * @brief Destroy a progress bar
 *
 * @param bar The progress bar to destroy
*/
void destroy_progress(progress_t *bar);

/**
 * @brief Calculate the distance between two points
 *
 * @param from The first point
 * @param to The second point
 *
 * @return The distance between the two points
*/
float distance_between_coords(sfVector2f from, sfVector2f to);

/**
 * @brief Create the inventory
 *
 * @return The newly created inventory
*/
inventory_t *create_inventory(void);

/**
 * @brief Analyse inventory events
 *
 * @param game The game structure
 * @param event The event to analyse
*/
void analyse_inventory_events(game_t *game, sfEvent *event);

/**
 * @brief Render the inventory
 *
 * @param window The render window on which the inventory is drawn
 * @param inventory The inventory to render
*/
void render_inventory(sfRenderWindow *window, inventory_t *inventory);

/**
 * @brief Destroy the inventory
 *
 * @param inventory The inventory to destroy
*/
void destroy_inventory(inventory_t *inventory);

/**
 * @brief Draw a sprite at the position of the sprite relative to the top-left
 * of the view, so view translation do not affect sprite position on the screen
 *
 * @param window,Render window on which the sprite is drawn
 * @param sprite The sprite to draw
*/
void view_drawsprite(sfRenderWindow *window, sfSprite *sprite);

/**
 * @brief Draw a sprite at a position relative to the top-left of the view
 * and the view size. Each component of the position of the sprite should be
 * set between 0 and 1, 0 meaning top/left and 1 meaning bottom/right
 *
 * @param window Rener window on which the sprite is drawn
 * @param sprite The sprite to draw
*/
void view_dynamic_drawsprite(sfRenderWindow *window, sfSprite *sprite);

/**
 * @brief Draw a text at the position of the text relative to the top-left
 * of the view, so view translation do not affect text position on the screen
 *
 * @param window,Render window on which the text is drawn
 * @param text The text to draw
*/
void view_drawtext(sfRenderWindow *window, sfText *text);

/**
 * @brief Draw a text at a position relative to the top-left of the view
 * and the view size. Each component of the position of the text should be
 * set between 0 and 1, 0 meaning top/left and 1 meaning bottom/right
 *
 * @param window Rener window on which the text is drawn
 * @param text The text to draw
*/
void view_dynamic_drawtext(sfRenderWindow *window, sfText *text);

/**
 * @brief Draw a text at the position of the text relative to the center
 * of the view, so view translation do not affect text position on the screen
 *
 * @param window,Render window on which the text is drawn
 * @param text The text to draw
*/
void view_center_drawtext(sfRenderWindow *window, sfText *text);

/**
 * @brief Creates the quests
 *
 * @param void Void
*/
quests_t *create_quests(void);

/**
 * @brief Anlyses the events of the quests
 *
 * @param game Game structure
 * @param event Event to analyse
*/
void analyse_quests_events(game_t *game, sfEvent *event);

/**
 * @brief Renders the quests
 *
 * @param window Window to draw on
 * @param quests quest structure
 * @param game game structure
*/
void render_quests(sfRenderWindow *window, quests_t *quests, game_t *game);

/**
 * @brief Destroys the quests
 *
 * @param quests quest structure
*/
void destroy_quests(quests_t *quests);

/**
 * @brief Check if the player collides with something and change move
 * accordingly
 *
 * @param game Pointer to the game structure
 * @param move Movement of the player
*/
void analyse_collision(game_t *game, sfVector2f *move);

/**
 * @brief Redirect the initialization to the appropriate function
 *
 * @param game Pointer to the game structure
 * @param step The step to redirect to
*/
void redirect_initialization(game_t *game, enum e_steps step);

/**
 * @brief Initialize the scene
 *
 * @param game Pointer to the game structure
 * @param step The step to initialize
*/
void initialize_scene(game_t *game, enum e_steps step);

/**
 * @brief Add an item to the inventory
 *
 * @param inventory The inventory to add the item to
 * @param item The item to add
 * @param quantity The quantity of the item to add
*/
void add_item_to_inventory(inventory_t *inventory,
    enum e_items item, unsigned int quantity);

/**
 * @brief Remove an item from the inventory
 *
 * @attention If the quantity of the item to remove is greater than the
 * quantity of the item in the inventory, nothing will happen
 *
 * @param inventory The inventory to remove the item from
 * @param item The item to remove
 * @param quantity The quantity of the item to remove
*/
void remove_item_from_inventory(inventory_t *inventory,
    enum e_items item, unsigned int quantity);

/**
 * @brief Use an item from the inventory
 *
 * @attention One item is removed from the inventory after being used
 *
 * @param game  A pointer to the game structure
 * @param item The item to use
*/
void use_item(game_t *game, enum e_items item);

/**
 * @brief Save the game
 *
 * @param game A pointer to the game structure to save
 * @param button A pointer to the button that triggered the action
*/
void save_game(game_t *game, __attribute__((unused)) button_t *button);

void analyse_experience(player_t *player);

/**
 * @brief Create the pause scene
 *
 * @return The pause scene
*/
pause_t *create_pause(void);

/**
 * @brief Render the pause scene
 *
 * @param window The window to render the pause scene on
 * @param pause The pause scene to render
*/
void render_pause(sfRenderWindow *window, pause_t *pause);

/**
 * @brief Analyses the events of the pause scene
 *
 * @param game A pointer to the game structure
 * @param event A pointer to the event to analyse
*/
void analyse_pause_events(game_t *game, sfEvent *event);

/**
 * @brief Destroy the pause scene
 *
 * @param game A pointer to the pause structure
*/
void destroy_pause(pause_t *pause);

/**
 * @brief Switch the scene to the boss scene
 *
 * @param game A pointer to the game structure
*/
void switch_to_boss(game_t *game);

void analyse_boss_events(game_t *game, __attribute__((unused)) sfEvent *event);
void render_boss(game_t *game);
void destroy_boss(boss_t *boss);
boss_t *create_boss(void);

/**
 * @brief Switch the player movement
 *
 * @param player The player to switch the movement of
 * @param move The movement to switch to
*/
void switch_player_movement(player_t *player, enum e_move move);

/**
 * @brief Create the resume scene
 *
 * @return The resume scene
*/
resume_t *create_resume(void);

/**
 * @brief Destroy the memory allocated to the resume scene
 *
 * @param resume A pointer to the resume scene
*/
void destroy_resume(resume_t *resume);

/**
 * @brief Render the resume scene
 *
 * @param game A pointer to the game structure
*/
void render_resume(game_t *game);

/**
 * @brief Analyses the events of the resume scene
 *
 * @param game A pointer to the game structure
 * @param event A pointer to the event to analyse
*/
void analyse_resume_events(game_t *game, sfEvent *event);

/**
 * @brief Switch the scene to the resume scene
 *
 * @param game A pointer to the game structure
 * @param button A pointer to the button that triggered the action
*/
void switch_to_resume(game_t *game, button_t *button);

/**
 * @brief Button to resume the game from a save
 *
 * @param game A pointer to the game structure
 * @param button A pointer to the button that triggered the action
*/
void resume_game(game_t *game, button_t *button);

/**
 * @brief Spawn the player in the game
 *
 * @param game A pointer to the game structure
*/
void spawn_player(game_t *game);


/**
* @brief Renders a button on the specified render window relative to the view
*
* @param window Pointer to the render window
* @param button Pointer to the button structure to be rendered
*/
void view_render_button(sfRenderWindow *window, button_t *button);

/**
* @brief Analyzes events specific to a button in a view
*
* @param game Pointer to the game structure
* @param event Pointer to the event to analyze
* @param button Pointer to the button to analyze events for
*/
void view_analyse_button_events(game_t *game,
    sfEvent *event, button_t *button);

/**
* @brief Checks if a point is within the bounds of a sprite in a view
*
* @param sprite Pointer to the sprite to check
* @param x X-coordinate of the point to be checked
* @param y Y-coordinate of the point to be checked
*
* @return Whether the point is within the bounds
*/
sfBool view_is_in_sprite(sfRenderWindow *window,
    sfSprite *sprite, float x, float y);

/**
 * @brief Initialises the rain particles
 *
 * @param void Void
*/
rain_t *init_rain(void);

/**
 * @brief Initialises the snow particles
 *
 * @param void Void
*/
snow_t *init_snow(void);

/**
 * @brief Updates the rain particles
 *
 * @param particles rain particles
 * @param time the time as seconds
*/
void update_rain(rain_t *particles, float time);

/**
 * @brief Updatess the snow particles
 *
 * @param particles rain particles
 * @param time the time as seconds
*/
void update_snow(snow_t *particles, float time);

/**
 * @brief Draws the rain particles
 *
 * @param window the window to draw on
 * @param particles the rain particles
*/
void draw_rain(sfRenderWindow *window, rain_t *particles);

/**
 * @brief Draws the snow particles
 *
 * @param window the window to draw on
 * @param particles the snow particles
*/
void draw_snow(sfRenderWindow *window, snow_t *particles);

/**
 * @brief Create a fade effect
 *
 * @return The fade effect
*/
fade_t *create_fade(void);

/**
 * @brief Update the fade effect
 *
 * @param fade The fade effect
*/
void update_fade(fade_t *fade);

/**
 * @brief Activate the fade effect
 *
 * @param fade The fade effect
*/
void activate_fade(fade_t *fade);

/**
 * @brief Destroy the fade effect
 *
 * @param fade The fade effect
*/
void destroy_fade(fade_t *fade);

/**
 * @brief Check if the current scene is a game scene
 *
 * @param scene The scene to check
 *
 * @return Whether the scene is a game scene
*/
bool is_game_scene(scene_t scene);

/**
 * @brief Pause menu action to resume the game
 *
 * @param game A pointer to the game structure
 * @param button A pointer to the button that triggered the action
*/
void pause_resume(game_t *game, button_t *button);

/**
 * @brief Pause menu action to quit the game
 *
 * @param game A pointer to the game structure
 * @param button A pointer to the button that triggered the action
*/
void pause_quit(game_t *game, button_t *button);

/**
 * @brief Set all the game menu state to closed
 *
 * @param player A pointer to the player structure
*/
void reset_menu_state(player_t *player);

/**
* @brief Draw the player on the screen
*
* @param window Render window to draw on
* @param player Player to draw
*/
void render_player(sfRenderWindow *window, player_t *player);

/**
 * @brief Handle player animation
 *
 * @param game Pointer to the game structure
*/
void player_attack(game_t *game);

/**
 * @brief Center the text of a button
 *
 * @param sprite The sprite of the button
 * @param text The text to center
 * @param offset An offset to apply on the y position
*/
void button_center_text(sfSprite *sprite, sfText *text, float offset);

/**
 * @brief Update the bind of an action
 *
 * @param game A pointer to the game structure
 * @param button A pointer to the button that triggered the action
*/
void update_keybind(game_t *game, button_t *button);

/**
 * @brief Save the keybinds to a configuration file
 *
 * @param keybinds The keybinds to save
*/
void save_keybinds(unsigned short *keybinds);

void increment_speed(quests_t *player);

zombie_t *create_mega(void);
void move_mega(game_t *game);
