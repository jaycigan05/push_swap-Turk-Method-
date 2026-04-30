/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:26:04 by jagan             #+#    #+#             */
/*   Updated: 2026/04/30 19:42:07 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

/*
The stack node. I use a singly linked list.
val = the actual integer value
index = its sorted rank (0,1,2,3,4...)
Assign the index after parsing (inout, error_msg) makes algo math easy
next = pointer to the node below it in the stack
*/

typedef struct s_stack
{
	int val;
	int index;
	struct  s_stack *next;
}   t_stack;

