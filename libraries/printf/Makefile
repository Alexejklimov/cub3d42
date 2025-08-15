# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oklimov <oklimov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/04 11:46:09 by oklimov           #+#    #+#              #
#    Updated: 2025/07/15 16:46:16 by oklimov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_printf.c print_char.c print_hex.c print_integer.c print_pointer.c \
			print_string.c print_unsigned.c ft_strlen.c ft_putchar_fd.c ft_putnbr_fd.c \
			ft_putstr_fd.c ft_calloc.c

NAME		= libftprintf.a

CC			= cc
CFLAGS		= -Wall -Werror -Wextra

OBJS		= ${SRCS:.c=.o}

all:	${NAME}



${NAME}:	${OBJS}
					@ar -rc ${NAME} ${OBJS}
					@ranlib ${NAME}

%.o: %.c
		@${CC} ${CFLAGS} -c $< -o $@

clean:
			@rm -f ${OBJS}

fclean:		clean
				@rm -f ${NAME}
				

re:			fclean all

.PHONY: all clean fclean re
