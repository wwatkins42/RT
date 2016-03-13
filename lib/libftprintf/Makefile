# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scollon <scollon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/11/25 13:40:40 by scollon           #+#    #+#              #
#    Updated: 2016/03/13 11:46:38 by scollon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH 	=	./src/
OBJ_PATH 	=	./obj/
LIB_PATH 	=	./libft/
INC_PATH 	=	./include/

NAME 		= 	libftprintf.a
CC 			=	 gcc
CFGLAGS		= 	-Werror -Wextra -Wall

SRC_NAME	= 	ft_printf.c ft_printf_fd.c check_err.c get_flags.c get_mods.c \
				get_prec.c get_width.c parse_format.c print_arg.c \
				print_arg_base.c print_arg_char.c print_arg_int.c print_arg_ptr.c \
				print_arg_str.c print_arg_unsigned.c nbr_len.c \
				nbr_len_base.c print_base.c print_char.c print_int.c print_mem.c \
				print_str.c print_unsigned_int.c str_len.c print_wchar.c \
				nbr_binary.c nbr_len_unsigned.c print_wstr.c \
				print_arg_notype.c is_type.c is_mod.c is_flag.c \
				print_arg_float.c  

OBJ_NAME 	= 	$(SRC_NAME:.c=.o)

SRC 		= 	$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ 		= 	$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INC 		= 	$(addprefix -I,$(INC_PATH))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2>/dev/null || echo "" > /dev/null
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

.PHONY: clean fclean re norm

clean:
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null

fclean: clean
	rm -f $(NAME)

re: fclean all

norm:
	norminette $(SRC_PATH) $(INC_PATH)
