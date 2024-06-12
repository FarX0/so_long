# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tfalchi <tfalchi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/17 14:57:10 by tfalchi           #+#    #+#              #
#    Updated: 2024/06/12 18:52:57 by tfalchi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc -Wall -Wextra -Werror -g

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libftprintf.a

NAME = so_long

MLX_DIR = ./minilibx
MLX = $(MLX_DIR)/libmlx.a
MLXFLAGS = -lX11 -lXext -lm

SRC =	utils.c \
		so_long.c \
		map_loading.c \
		game_logic.c \
		utils2.c \
		utils3.c \
		utils4.c \
		utils5.c 

##	flood_fill.c  ft_error_free.c  ft_errors.c  \
	map_check.c put_images.c  read_map.c  so_long.c \
	bad_next_line.c get_entity.c check_this_moves.c \
	enemy_bonus.c put_lights.c images.c movements.c key_imput.c \
	flooding_light.c frees.c check_moves2.c animations_bonus.c


OBJ = $(SRC:.c=.o)

all: $(NAME)

val:
	@rm -f $(NAME)
	@$(CC) $(SRC) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "\033[34mAre you ready for debugging?\033[0m 😈"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./$(NAME) .vscode/map2.ber

download:
				wget -q https://cdn.intra.42.fr/document/document/21656/minilibx-linux.tgz; \
				tar -xf minilibx-linux.tgz; \
				mv minilibx-linux minilibx; \
				rm -f minilibx-linux.tgz; \

$(NAME): $(OBJ)
	@make all -C $(LIBFT_DIR)
	@make all -C $(MLX_DIR)
	@$(CC) $(OBJ) $(LIBFT) $(MLX) $(MLXFLAGS) -o $(NAME)
	@echo "Compiled "$(NAME)" successfully!"

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@make clean -C $(LIBFT_DIR)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re redo
