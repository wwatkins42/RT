# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollon <scollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/04/27 11:30:14 by scollon           #+#    #+#              #
#    Updated: 2016/04/28 08:46:49 by scollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ../lib/
INC_PATH = ./include/ $(LIB_PATH)libft/include/ $(LIB_PATH)libvec/include/ \
			$(LIB_PATH)libftprintf/include/

NAME = Raytracer
CC = gcc
CFLGS = -Werror -Wextra -Wall \
		`~/.brew/Cellar/pkg-config/0.29.1/bin/pkg-config --cflags gtk+-3.0`
CLIBS = `~/.brew/Cellar/pkg-config/0.29.1/bin/pkg-config --libs gtk+-3.0`
MLXFLGS = -framework OpenGL -framework AppKit

SRC_NAME = 	main.c error_ui.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft libftprintf

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB	= $(addprefix -L$(LIB_PATH),$(LIB_NAME))

.PHONY: re all clean fclean nolib norme

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	make -C $(LIB_PATH)libftprintf -j
	$(CC) $(CFLGS) $(CLIBS) $(LIB) -lft -lftprintf $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLGS) $(INC) -o $@ -c $<

nolib: $(OBJ)
	$(CC) $(CFLGS) -lft -lftprintf $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	make -C $(LIB_PATH)libftprintf fclean
	rm -fv $(NAME)

re: fclean all

norme:
	make -C $(LIB_PATH) norme
	make -C $(VEC_PATH) norme
	norminette $(SRC) ./include/
