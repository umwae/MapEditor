# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 15:55:47 by jsteuber          #+#    #+#              #
#    Updated: 2019/09/19 20:14:01 by jsteuber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Editor

CFLAGS=#-Wall -Wextra -Werror
FFLAGS=-framework OpenGL -framework AppKit
#FFLAGS= -lXext -lX11 -lm

SRC_PATH=./src
INC_PATH=./include
#MLX_PATH=./minilibx
MLX_PATH=./minilibx_macos
MLX_INC_PATH=/usr/X11/include
FT_PATH=./libft
BIN_PATH=./bin

SRC= main.c image.c init.c show.c actions.c walls.c selection.c utilities.c \
context_menu.c gui.c sectors.c messages.c colors.c output.c input.c grid.c \
objects.c player.c info_menu.c sec_list.c
OBJ:= $(addprefix $(BIN_PATH)/,$(SRC:.c=.o))

.PHONY: all clean fclean re

all: $(BIN_PATH) $(NAME)

$(BIN_PATH):
	mkdir -p bin

$(NAME): $(OBJ) $(INC_PATH)/editor.h
	@make -s -C $(FT_PATH)
	gcc -o $@ $(OBJ) -L$(MLX_PATH) -lmlx -I$(MLX_INC_PATH) -L$(FT_PATH) -lft -I$(FT_PATH) $(FFLAGS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.c
	gcc -g $(CFLAGS) -o $@ -c $< -I$(INC_PATH) -I$(FT_PATH)

clean:
	@make -s -C $(FT_PATH) fclean
	rm -rf $(BIN_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
