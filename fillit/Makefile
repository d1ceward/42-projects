# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flefebvr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/04 18:14:21 by flefebvr          #+#    #+#              #
#    Updated: 2016/01/08 20:01:20 by flefebvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
GCC_FLAGS = -Wall -Wextra -Werror
CC = gcc $(GCC_FLAGS)
RM = rm -rf
SRCS = \
	main.c \
	check.c \
	init.c \
	solver.c \
	print.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C libft/
	@$(CC) -Llibft $(OBJS) -lft -o $(NAME)

%.o: %.c
	@$(CC) -o $@ -c $^

clean:
	@make -C libft clean
	@$(RM) $(OBJS)

fclean: clean
	@make -C libft fclean
	@$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all
