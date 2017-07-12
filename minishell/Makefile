# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/18 17:43:32 by flefebvr          #+#    #+#              #
#    Updated: 2017/03/29 09:59:50 by flefebvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

# Configs
CFLAGS       = -Weverything
INC_DIR_LIBFT = libft/includes/
INCLUDES_DIR = includes/
SRC_DIR      = srcs/
OBJ_DIR      = objs/
vpath %.c srcs

# Sources/objects files
SRCS	= main.c builtin.c utils.c cd.c
SOURCES = $(addprefix $(SRC_DIR), $(SRCS))
OBJECTS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# Colors
OK_C     = \033[32;01m
SILENT_C = \033[30;01m
WARN_C   = \033[33;01m
ERROR_C  = \033[31;01m
NO_C     = \033[0m

# Rules
all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C libft/
	@printf "| $(ERROR_C)=>$(NO_C) $(SILENT_C)Minishell:$(NO_C)%-37s" \
		" Compiling ..."
	@clang $(CFLAGS) $(OBJECTS) -L libft/ -lft -o $(NAME)
	@printf "[$(OK_C)DONE$(NO_C)]\n"
	
objs/%.o: %.c
	@mkdir -p $(dir $@)
	@clang $(CFLAGS) -I $(INC_DIR_LIBFT) \
		-I $(INCLUDES_DIR) -c $(subst __,/,$<) -o $@
	@printf "| $(SILENT_C)=>$(NO_C)%-48s[$(OK_C)OK$(NO_C)]\n" " $<"
	
clean:
	@printf "| $(ERROR_C)=>$(NO_C) $(SILENT_C)Minishell:$(NO_C)%-37s" \
		" Removed objects"
	@rm -rf $(OBJ_DIR)
	@printf "[$(WARN_C)DONE$(NO_C)]\n"

fclean: clean
	@printf "| $(ERROR_C)=>$(NO_C) $(SILENT_C)Minishell:$(NO_C)%-37s" \
		" Removed library and executable"
	@rm -f $(NAME)
	@printf "[$(WARN_C)DONE$(NO_C)]\n"
	@make -C libft/ fclean

re: fclean all

.PHONY: re fclean clean all
