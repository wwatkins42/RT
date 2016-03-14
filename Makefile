# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 11:45:04 by wwatkins          #+#    #+#              #
#    Updated: 2016/03/14 10:45:48 by wwatkins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./include/ $(LIB_PATH)libft/include/ $(LIB_PATH)libvec/include/ \
			$(LIB_PATH)libftprintf/include/

NAME = rt
VIEWER = ./viewer/
CC = gcc
CFLGS = -Werror -Wextra -Wall
MLXFLGS = -framework OpenGL -framework AppKit

SRC_NAME = 	main.c parse.c create_camera.c create_light.c create_object.c \
			utils.c error.c init.c core.c draw.c hook.c viewer_export.c \
			raytracing_color.c raytracing_intersect.c raytracing.c \
			raytracing_recursion.c bmp_exporter.c yml_exporter.c yml_write.c \
			filter.c


OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft libftprintf libvec mlx

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB	= $(addprefix -L$(LIB_PATH),$(LIB_NAME))

.PHONY: re all clean fclean nolib norme

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft
	make -C $(LIB_PATH)mlx
	make -C $(LIB_PATH)libftprintf
	make -C $(LIB_PATH)libvec
	make -C $(VIEWER) re
	$(CC) $(CFLGS) $(LIB) -lft -lftprintf -lvec -lmlx $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLGS) $(INC) -o $@ -c $<

nolib: $(OBJ)
	$(CC) $(CFLGS) -lft -lftprintf -lvec -lmlx $(INC) $(OBJ) $(MLXFLGS) -o $(NAME)

clean:
	rm -fv $(OBJ)
	rm -rf $(OBJ_PATH)

fclean: clean
	make -C $(LIB_PATH)libft fclean
	make -C $(LIB_PATH)libftprintf fclean
	make -C $(LIB_PATH)libvec fclean
	make -C $(LIB_PATH)mlx clean
	make -C $(VIEWER) fclean
	rm -fv $(NAME)

re: fclean all

norme:
	make -C $(LIB_PATH) norme
	make -C $(VEC_PATH) norme
	norminette $(SRC) ./include/
