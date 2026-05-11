# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/11 10:48:10 by jagan             #+#    #+#              #
#    Updated: 2026/05/11 10:56:11 by jagan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = cc
FLAGS = -Wall _Wextra -Werror
AR = ar rcs
RM = rm -f

SRC = main \
		ops_push \
		ops_reverse_rotate \
		ops_rotate \
		ops_swap \
		sb_calc_cost \
		sb_find_target \
		sort_big \
		sort_small \
		stack_init \
		stack_utils \
		utils \

SRC := $(SRC:% = %.c)