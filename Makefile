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

SRCS		:= src/cub3d.c src/parsing/read_and_separate.c src/utils/utils.c	\
			src/parsing/parsing_utils.c src/parsing/parse_map.c					\
			src/raycasting/handle_movement.c src/raycasting/raycasting.c		\
			src/raycasting/render.c src/raycasting/render_utils.c src/init.c	\
			src/init_mlx.c src/raycasting/color_utils.c src/utils/clean.c		\
			src/parsing/parsing_utils2.c										\

BONUS_SRCS	:= src/bonus/render_mini_map.c src/bonus/init_minimap.c				\
			src/bonus/draw.c													\

OBJS		:= $(SRCS:%.c=%.o)

BONUS_OBJS	:= $(BONUS_SRCS:%.c=%.o)

LIBFT_DIR	:= libraries/libft
PRINTF_DIR	:= libraries/printf
MLX_DIR		:= libraries/MLX42

LIBFT		:= $(LIBFT_DIR)/libft.a
PRINTF		:= $(PRINTF_DIR)/libftprintf.a
LIBMLX		:= $(MLX_DIR)/build/libmlx42.a

LIBS		:= $(LIBFT) $(PRINTF) $(LIBMLX)

MLX_URL		:= https://github.com/codam-coding-college/MLX42.git

HEADERS 	:= -I./inc -I./$(PRINTF_DIR)/include -I./$(LIBFT_DIR)

CC			= cc
CFLAGS		= -Wall -Werror -Wextra -O3
CFLAGS		= -Wall -Werror -Wextra -O3 -fsanitize=address -fsanitize=undefined
MLX_FLAGS 	= -ldl -lglfw -pthread -lm

$(NAME): ${LIBMLX} ${PRINTF} ${LIBFT} $(OBJS)
# 	@${CC} ${OBJS} -o ${NAME} ${LIBS} ${MLX_FLAGS}
	@${CC} ${OBJS} -o ${NAME} ${LIBS} ${MLX_FLAGS} -fsanitize=address -fsanitize=undefined
	@echo "Mandatory version compiled successfully!"

%.o: %.c
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "Compiled: $<"

src/bonus/%.o: src/bonus/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -D BONUS=1 -c src/cub3d.c -o src/cub3d.o
	@$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@
	@echo "Compiled bonus: $<"

all: $(NAME)

bonus: ${LIBMLX} ${PRINTF} ${LIBFT} $(OBJS) $(BONUS_OBJS) 
	@${CC} ${OBJS} $(BONUS_OBJS) -o ${NAME} ${LIBS} ${MLX_FLAGS}
	@echo "Bonus version compiled successfully!"

clean:
	@rm -f $(OBJS) $(BONUS_OBJS)
	@rm -rf $(MLX_DIR)/build
	@make --no-print-directory -C libraries/printf clean
	@make --no-print-directory -C libraries/libft clean

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(MLX_DIR)/build
	@make --no-print-directory -C $(PRINTF_DIR) fclean
	@make --no-print-directory -C libraries/libft fclean


re: fclean all

${LIBFT}:
	@make -C libraries/libft

$(PRINTF):
	@make --no-print-directory -C libraries/printf

$(LIBMLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning repository..."; \
		git clone $(MLX_URL) $(MLX_DIR); \
	fi
	@cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

.PHONY: all clean fclean re bonus