# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/26 16:00:59 by flefebvr          #+#    #+#              #
#    Updated: 2016/03/03 17:51:05 by flefebvr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Configs
CFLAGS       = -Wall -Wextra -Werror
INCLUDES_DIR = includes/
SRC_DIR      = srcs/
OBJ_DIR      = objs/
vpath %.c srcs

# Sources/objects files
SRC_CONVERT = ft_abs.c ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c
SRC_LISTS   = ft_lstadd.c ft_lstdel.c ft_lstdelone.c ft_lstiter.c \
ft_lstmap.c ft_lstnew.c ft_lstpushback.c
SRC_MATH    = ft_sqrt.c ft_max.c ft_min.c
SRC_MEMORY  = ft_bzero.c ft_memalloc.c ft_memccpy.c ft_memchr.c \
ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c
SRC_PRINT   = ft_exit.c ft_putchar.c ft_putchar_fd.c ft_putendl.c \
ft_putendl_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putstr.c ft_putstr_fd.c \
ft_putnstr.c ft_putnstr_fd.c ft_putwchar.c ft_putwchar_fd.c ft_putwstr.c \
ft_putwstr_fd.c ft_putnwstr.c ft_putnwstr_fd.c ft_putnbrbase.c \
ft_putnbrbase_fd.c
SRC_STRINGS = ft_strcat.c ft_strchr.c ft_strclr.c ft_strcmp.c ft_strcpy.c \
ft_strdel.c ft_strdup.c ft_strequ.c ft_striter.c ft_striteri.c ft_strjoin.c \
ft_strlcat.c ft_strlen.c ft_strmap.c ft_strmapi.c ft_strncat.c ft_strncmp.c \
ft_strncpy.c ft_strndup.c ft_strnequ.c ft_strnew.c ft_strnstr.c ft_strrchr.c \
ft_strsplit.c ft_strstr.c ft_strsub.c ft_strtrim.c ft_strnlen.c ft_wstrlen.c \
ft_stradd.c
SRC_UTILITY = ft_digit_count.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
ft_isdigit.c ft_isprint.c ft_isspace.c get_next_line.c

# Folder manipulation
SRCS = \
	$(addprefix convert/, $(SRC_CONVERT)) \
	$(addprefix lists/, $(SRC_LISTS)) \
	$(addprefix math/, $(SRC_MATH)) \
	$(addprefix memory/, $(SRC_MEMORY)) \
	$(addprefix print/, $(SRC_PRINT)) \
	$(addprefix strings/, $(SRC_STRINGS)) \
	$(addprefix utility/, $(SRC_UTILITY))
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
	@printf "| $(ERROR_C)=>$(NO_C) $(SILENT_C)Libft:$(NO_C)%-41s" \
		" Compiling ..."
	@ar rcs $(NAME) $(OBJECTS)
	@printf "[$(OK_C)DONE$(NO_C)]\n"
	
objs/%.o: %.c
	@mkdir -p $(dir $@)
	@gcc $(CFLAGS) -I $(INCLUDES_DIR) -c $(subst __,/,$<) -o $@
	@printf "| $(SILENT_C)=>$(NO_C)%-48s[$(OK_C)OK$(NO_C)]\n" " $<"

clean:
	@printf "| $(ERROR_C)=>$(NO_C) $(SILENT_C)Libft:$(NO_C)%-41s" \
		 " Removed objects"
	@rm -rf $(OBJ_DIR)
	@printf "[$(WARN_C)DONE$(NO_C)]\n"

fclean: clean
	@printf "| $(ERROR_C)=>$(NO_C) $(SILENT_C)Libft:$(NO_C)%-41s" \
		" Removed library"
	@rm -f $(NAME)
	@printf "[$(WARN_C)DONE$(NO_C)]\n"

re: fclean all

.PHONY: re fclean clean all
