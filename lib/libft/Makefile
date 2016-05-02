# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollon <scollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/15 09:15:55 by wwatkins          #+#    #+#              #
#    Updated: 2016/04/30 09:40:05 by scollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

NAME = libft.a
CC = gcc
CFGLAGS = -Werror -Wextra -Wall

SRC_NAME  = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strlen.c ft_strdup.c ft_strcpy.c \
			ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
			ft_strrchr.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
			ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
			ft_isprint.c ft_tolower.c ft_toupper.c ft_memalloc.c ft_memdel.c \
			ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
			ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
			ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c \
			ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_nbrlen.c ft_lstnew.c ft_lstdelone.c \
			ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strrev.c \
			ft_nbrlen.c ft_wordcount.c ft_isblank.c ft_itoa_base.c ft_atoi_base.c \
			ft_atof.c get_next_line.c ft_clamp.c ft_pow.c ft_boolean.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

norme:
	norminette $(SRC) $(INC_PATH)libft.h

clean:
	rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
