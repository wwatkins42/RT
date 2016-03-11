# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollon <scollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 11:45:04 by wwatkins          #+#    #+#              #
#    Updated: 2016/03/11 09:26:27 by scollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ../lib/
INC_PATH = ./include/ ../include/ $(LIB_PATH)libft/include/ \
			$(LIB_PATH)libftprintf/include/

NAME = image_viewer
CC = gcc
CFLGS = -Werror -Wextra -Wall
MLXFLGS = -framework OpenGL -framework AppKit

SRC_NAME = 	main.c viewer_import.c hook.c error.c filter.c bmp_exporter.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft libftprintf mlx

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB	= $(addprefix -L$(LIB_PATH),$(LIB_NAME))

.PHONY: re all clean fclean nolib

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLGS) $(LIB) -lft -lftprintf -lmlx $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)
	mv $(NAME) ../

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLGS) $(INC) -o $@ -c $<

nolib: $(OBJ)
	$(CC) $(CFLGS) -lft -lftprintf -lmlx $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -fv ../$(NAME)

re: fclean all
