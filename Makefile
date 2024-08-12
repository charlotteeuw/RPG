##
## EPITECH PROJECT, 2024
## my_rpg
## File description:
## Makefile
##

MAIN = src/main.c

SRC = src/tools.c \
	src/game/create/create.c \
	src/game/create/initialize.c \
	src/game/create/scene.c \
	src/game/destroy.c \
	src/game/events.c \
	src/game/render.c \
	src/scene/boss/boss_fight.c \
	src/scene/boss/boss.c \
	src/logic/list.c \
	src/logic/window.c \
	src/logic/movement/move_cat.c \
	src/logic/movement/move_player.c \
	src/logic/movement/animate_player.c \
	src/logic/movement/movement.c \
	src/logic/movement/collision.c \
	src/logic/movement/animate_attack.c \
	src/logic/inventory/manage_inventory.c \
	src/logic/inventory/user_inventory.c \
	src/logic/inventory/analyse_inventory.c \
	src/logic/dialogue.c \
	src/logic/distances.c \
	src/logic/keybinds.c \
	src/logic/npc.c	\
	src/logic/quests/manage_quests.c \
	src/logic/quests/render_quests.c \
	src/logic/backup/save.c \
	src/logic/backup/load.c \
	src/logic/pause/manage_pause.c \
	src/logic/pause/pause_actions.c \
	src/logic/player.c \
	src/logic/particles.c	\
	src/logic/zoom.c \
	src/logic/view/view_sprite.c \
	src/logic/view/view_text.c \
	src/logic/view/view_button.c \
	src/logic/view/view.c \
	src/objects/button.c \
	src/objects/fade.c \
	src/objects/progress.c \
	src/objects/rect.c \
	src/objects/slider.c \
	src/objects/sprite.c \
	src/objects/text.c \
	src/objects/textbox.c \
	src/objects/volume.c \
	src/scene/settings/analyse_settings.c \
	src/scene/settings/framerate_settings.c \
	src/scene/settings/manage_settings.c \
	src/scene/settings/render_settings.c \
	src/scene/settings/windows_settings.c \
	src/scene/title/manage_title.c \
	src/scene/title/title_actions.c \
	src/scene/selection/manage_selection.c \
	src/scene/selection/create_selection.c \
	src/scene/outside/analyse_outside.c \
	src/scene/outside/manage_outside.c \
	src/scene/outside/render_outside.c \
	src/scene/resume.c \
	src/scene/tuto.c \
	src/scene/utils.c \
	src/scene/spawn.c \
	src/scene/shop.c \
	src/scene/sheriff.c	\
	src/scene/room.c \
	src/scene/zombie.c
OBJ	= $(SRC:.c=.o) $(MAIN:.c=.o)

SRC_LIB = src/utils/my_itoa.c \
	src/utils/my_nbrlen.c \
	src/utils/my_open.c \
	src/utils/my_puts.c \
	src/utils/my_strcat.c \
	src/utils/my_strcpy.c \
	src/utils/my_strdup.c \
	src/utils/my_strlen.c \
	src/utils/my_splitstr.c	\
	src/utils/my_freearray.c
OBJ_LIB = $(SRC_LIB:.c=.o)

SRC_UT = tests/utils/test_my_itoa.c \
	tests/utils/test_my_open.c \
	tests/utils/test_my_puts.c \
	tests/utils/test_my_strcat.c \
	tests/utils/test_my_strcpy.c \
	tests/utils/test_my_strdup.c \
	tests/utils/test_my_strlen.c

SANFLAGS =
# SANFLAGS = -fsanitize=address,undefined -fno-omit-frame-pointer

CFLAGS += -I./include/ -g -Wall -Wextra -Wpedantic $(SANFLAGS)
LDFLAGS += $(SANFLAGS)

LDLIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lcsfml-audio -lm

NAME = my_rpg

LIB = libmy.a

UNIT = unit_tests

$(NAME): $(OBJ) $(LIB)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LOADLIBES)

$(LIB): $(OBJ_LIB)
	$(AR) $(ARFLAGS) $@ $^

$(UNIT): $(SRC) $(SRC_LIB) $(SRC_UT)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS) $(LOADLIBES) -lcriterion --coverage

all: $(NAME)

tests_run: fclean $(UNIT)
	./$(UNIT)

clean:
	find -type f -name '*.gc*' -delete
	find -type f -name '*.o' -delete

fclean: clean
	find -type f -name '$(NAME)' -delete -o -type f -name '$(UNIT)' -delete
	find -type f -name '$(LIB)' -delete

re: fclean all

.PHONY: all tests_run clean fclean re
