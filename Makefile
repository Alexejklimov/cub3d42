# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 11:46:09 by oklimov           #+#    #+#              #
#    Updated: 2025/07/15 16:54:05 by oklimov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:=	cub3d

SRCS		:= src/cub3d.c src/parsing/read_and_separate.c src/render_utils.c	\
			src/utils/utils.c src/parsing/parsing_utils.c src/init.c src/draw.c \
			src/handle_movement.c src/raycasting.c src/render.c					\
			src/render_mini_map.c src/init_minimap.c src/parsing/parse_map.c	\

OBJS		:= $(SRCS:%.c=%.o)

LIBFT_DIR	:= libraries/libft
PRINTF_DIR	:= libraries/printf
MLX_DIR		:= libraries/MLX42
OBJ_DIR		:= .build

LIBFT		:= $(LIBFT_DIR)/libft.a
LIBMLX		:= $(MLX_DIR)/build/libmlx42.a
PRINTF		:= $(PRINTF_DIR)/libftprintf.a

MLX_URL		:= https://github.com/codam-coding-college/MLX42.git

# HEADERS 	:= -I./inc -I./$(PRINTF_DIR)/include -I./$(MLX_DIR)/include -I./$(LIBFT_DIR)
HEADERS 	:= -I./inc -I./$(PRINTF_DIR)/include -I./$(LIBFT_DIR)

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3 -g
MLX_FLAGS 	= -ldl -lglfw -pthread -lm

$(NAME): $(OBJS) ${LIBMLX} ${PRINTF} ${LIBFT}
	@${CC} ${OBJS} -o ${NAME} ${PRINTF} ${LIBFT} ${LIBMLX} ${MLX_FLAGS}

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@


all: $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -rf $(MLX_DIR)/build
	@make --no-print-directory -C libraries/printf clean
	@make --no-print-directory -C libraries/libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build
	@make --no-print-directory -C $(PRINTF_DIR) fclean
	@make --no-print-directory -C libraries/libft fclean


re: fclean all

$(PRINTF):
	@make --no-print-directory -C libraries/printf

$(LIBMLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning repository..."; \
		git clone $(MLX_URL) $(MLX_DIR); \
	fi
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

${LIBFT}:
	@make -C libraries/libft

.PHONY: all clean fclean re build