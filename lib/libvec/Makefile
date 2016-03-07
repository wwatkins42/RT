# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wwatkins <wwatkins@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/27 14:31:06 by wwatkins          #+#    #+#              #
#    Updated: 2016/03/02 16:02:05 by wwatkins         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
OBJ_PATH = ./obj/
INC_PATH = ./include/

NAME = libvec.a
CC = gcc
CFGLAGS = -Werror -Wextra -Wall

SRC_NAME = vec2.c vec2i.c vec2_add.c vec2_sub.c vec2_mul.c vec2_fmul.c \
		   vec2_dot.c vec2_rot.c vec2_magnitude.c vec2_normalize.c vec2_scale.c \
		   vec3_zero.c vec3_up.c vec3_right.c vec3_forward.c vec3.c vec3i.c \
		   vec3_add.c vec3_sub.c vec3_mul.c vec3_fmul.c vec3_dot.c vec3_rot.c \
		   vec3_clamp.c vec3_rotate.c vec3_cross.c vec3_norm.c vec3_reflect.c \
		   vec3_scale.c vec3_magnitude.c vec3_normalize.c

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
	norminette $(SRC) $(INC_PATH)libvec.h

clean:
	rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
