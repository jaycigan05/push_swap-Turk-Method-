# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/11 10:48:10 by jagan             #+#    #+#              #
#    Updated: 2026/05/20 17:05:34 by jagan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
CFLAG = -Wall -Wextra -Werror
RM = rm -f

SRC = main.c \
		ops_push.c \
		ops_rotate.c \
		ops_swap.c \
		sb_calc_cost.c \
		sb_find_target.c \
		sort_big.c \
		sort_small.c \
		stack_init.c \
		stack_utils.c \
		utils.c

OBJ = $(SRC:%.c=%.o)

%.o = %.c
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
