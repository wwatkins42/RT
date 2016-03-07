# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 11:45:04 by wwatkins          #+#    #+#              #
#    Updated: 2016/03/07 11:46:19 by wwatkins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/ ./lib/libft/include/ ./lib/libvec/include
LIB_PATH = ./lib/libft/
VEC_PATH = ./lib/libvec/
MLX_PATH = ./lib/minilibx_macos

NAME = rt
CC = gcc
CFLGS = -Werror -Wextra -Wall -Ofast
MLXFLGS = -L$(MLX_PATH) -I$(MLX_PATH) -lmlx \
		  -framework OpenGL -framework AppKit

SRC_NAME = main.c
OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft.a
VEC_NAME = libvec.a

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB = $(LIB_PATH)$(LIB_NAME)
VEC = $(VEC_PATH)$(VEC_NAME)

.PHONY: re all clean fclean cleanmlx cleanvec fcleanvec cleanlib \
		fcleanlib nolib norme

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLX_PATH) re
	make -C $(VEC_PATH) re
	make -C $(LIB_PATH) re
	$(CC) $(CFLGS) $(LIB) $(VEC) $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLGS) $(INC) -o $@ -c $<

nolib: $(OBJ)
	$(CC) $(CFLGS) $(LIB) $(VEC) $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

cleanmlx:
	make -C $(MLX_PATH) clean

cleanlib:
	make -C $(LIB_PATH) clean

cleanvec:
	make -C $(VEC_PATH) clean

fcleanvec:
	make -C $(VEC_PATH) fclean

fcleanlib:
	make -C $(LIB_PATH) fclean

clean: cleanmlx cleanlib cleanvec
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean fcleanlib fcleanvec
	rm -fv $(NAME)

re: fclean all

norme:
	make -C $(LIB_PATH) norme
	make -C $(VEC_PATH) norme
	norminette $(SRC) ./include/
