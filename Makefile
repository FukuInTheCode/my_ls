##
## EPITECH PROJECT, 2023
## my_ls Makefile
## File description:
## Placeholder
##

NAME   = my_ls

CC	   = gcc

CFLAGS = -Wall -Wextra -Wno-unused-value -Wno-sign-compare \
	-Wno-unused-parameter -I./include

CSFML = -lcsfml-system -lcsfml-window -lcsfml-network \
			-lcsfml-graphics -lcsfml-audio

CRITERION = -lcriterion

LIBS = -L./lib/my_printf -lmy_printf

SRC	= my_ls.c \
		flags/l_flags.c \
		flags/d_flags.c \
		flags/r_flags.c \
		flags/t_flags.c \
		flags/rmaj_flags.c \
		flags/a_flags.c \
		handle_dir.c \
		handle_file.c \
		my_advanced_sort_word_array.c \
		my_advanced_sort_entry_array.c \
		my_strcmp.c \
		my_cmp.c \

OBJ	= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C./lib/my_printf re
	@$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LIBS)

clean:
	@rm -f $(OBJ)
	@make -C./lib/my_printf clean

fclean: clean
	@rm -f $(NAME)
	@make -C./lib/my_printf fclean

re: fclean all
