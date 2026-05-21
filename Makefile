# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/11 10:48:10 by jagan             #+#    #+#              #
#    Updated: 2026/05/21 11:20:43 by jagan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -f

SRC = src/main.c \
		src/ops_push.c \
		src/ops_reverse_rotate.c \
		src/ops_rotate.c \
		src/ops_swap.c \
		src/sb_calc_cost.c \
		src/sb_find_target.c \
		src/sort_big.c \
		src/sort_small.c \
		src/stack_init.c \
		src/stack_utils.c \
		src/utils.c \
		src/ft_split.c \

OBJ = $(SRC:%.c=%.o)

%.o : %.c
	$(CC) $(CFLAG) -I. -c $< -o $@

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAG) $(OBJ) -o $(NAME)
	echo "$(NAME) is created."

clean :
	$(RM) $(OBJ)
	echo "Removed object files."

fclean : clean
	$(RM) $(NAME)
	echo "Removed $(NAME)"

re : fclean all

.PHONY : all clean fclean re
