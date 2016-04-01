# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollon <scollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/03/07 11:45:04 by wwatkins          #+#    #+#              #
#    Updated: 2016/04/01 11:44:05 by scollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
LIB_PATH = ./lib/
INC_PATH = ./include/ $(LIB_PATH)libft/include/ $(LIB_PATH)libvec/include/ \
			$(LIB_PATH)libftprintf/include/

NAME = rt
CC = gcc
CFLGS = -Werror -Wextra -Wall -Ofast
MLXFLGS = -framework OpenGL -framework AppKit

SRC_NAME = 	main.c parse_yml.c parse.c parse_camera.c parse_light.c \
			parse_object.c parse_utils.c parse_material.c noise.c \
			utils.c error.c init.c core.c draw.c hook.c \
			raytracing_color.c raytracing_intersect.c raytracing.c \
			raytracing_recursion.c bmp_exporter.c yml_exporter.c yml_write.c \
			filter.c antialiasing.c bmp_importer.c texture.c movement.c \
			texture_generator.c normal_map.c mouse_hook.c intersect_cube.c \
			intersect_hyperboloid.c intersect_paraboloid.c \
			intersect_parallelogram.c intersect_torus.c intersect_triangle.c \
			solve_quartic.c fresnel.c raytracing_shadow.c object_movement.c

OBJ_NAME = $(SRC_NAME:.c=.o)
LIB_NAME = libft libftprintf libvec mlx

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))
LIB	= $(addprefix -L$(LIB_PATH),$(LIB_NAME))

.PHONY: re all clean fclean nolib norme

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(LIB_PATH)libft -j
	make -C $(LIB_PATH)mlx -j
	make -C $(LIB_PATH)libftprintf -j
	make -C $(LIB_PATH)libvec -j
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
	rm -fv $(NAME)

re: fclean all

norme:
	make -C $(LIB_PATH) norme
	make -C $(VEC_PATH) norme
	norminette $(SRC) ./include/
