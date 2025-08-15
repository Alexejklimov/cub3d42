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

NAME = cub3d

SRCS =  cub3d.c src/parsing/read_and_separate.c src/parsing/parse_map.c \
		src/utils/utils.c src/parsing/parsing_utils.c \

OBJS = $(SRCS:.c=.o)

LIBFT = libraries/libft/libft.a


LIBMLX = libraries/MLX42

PRINTF = libraries/printf/libftprintf.a

CC = cc
CFLAGS = -Wall -Werror -Wextra -I./libraries/printf -I./libraries/minilibx-linux -I./libraries/libft -I./libraries/gnl -g
MLX_FLAGS = -Llibraries/minilibx-linux -lmlx -L/usr/lib/X11 -lXext -lX11

$(NAME): $(OBJS) ${LIBMLX} ${PRINTF} ${LIBFT}
	@${CC} ${OBJS} -o ${NAME} ${PRINTF} ${LIBFT} ${LIBMLX} ${MLX_FLAGS}

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: build

clean:
	@rm -f $(OBJS)
	@make --no-print-directory -C libraries/printf clean
	@make --no-print-directory -C libraries/libft clean

fclean: clean
	@rm -f $(NAME)
	@make --no-print-directory -C libraries/printf clean
	@make --no-print-directory -C libraries/libft clean


re: fclean all

$(PRINTF):
	@make --no-print-directory -C libraries/printf

$(LIBMLX):
	@make -C libraries/minilibx-linux

${LIBFT}:
	@make -C libraries/libft

.PHONY: all clean fclean re build

STEPS = 25

build:
	@if make -q ${NAME}; then \
		echo "make: Nothing to be done for 'all'."; \
	else \
		i=1; \
		while [ $$i -le $(STEPS) ]; do \
			percent=$$((4 * $$i)); \
			bar_len=$$((percent)); \
			if   [ $$percent -le 10 ];  then color="\033[38;5;160m"; \
			elif [ $$percent -le 20 ];  then color="\033[38;5;196m"; \
			elif [ $$percent -le 30 ];  then color="\033[38;5;202m"; \
			elif [ $$percent -le 40 ];  then color="\033[38;5;226m"; \
			elif [ $$percent -le 50 ];  then color="\033[38;5;190m"; \
			elif [ $$percent -le 60 ];  then color="\033[38;5;154m"; \
			elif [ $$percent -le 70 ];  then color="\033[38;5;118m"; \
			elif [ $$percent -le 80 ];  then color="\033[38;5;82m"; \
			elif [ $$percent -le 90 ];  then color="\033[38;5;46m"; \
			else                          color="\033[38;5;40m"; fi; \
			bar="$$(printf '█%.0s' $$(seq 1 $$bar_len))"; \
			printf "\r\033[36mProgress: %3d%% \033[0m $${color}%-25s\033[0m" $$percent "$$bar "; \
			i=$$((i + 1)); \
			sleep 0.01; \
		done; \
		printf "\n"; \
		make -s ${NAME}; \
	fi
