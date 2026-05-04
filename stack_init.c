/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:44:47 by jagan             #+#    #+#             */
/*   Updated: 2026/05/04 10:21:29 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Print "Error\n" to stderr; free stack and exit
when found non-integer/ out of range/ duplicate
** exit = stop immediately of the whole programme 
to prevent keep running
*/

void	ft_error(t_stack **a)
{
	ft_free(a);
	write(2, "Error\n", 6);
	exit(1);
}

/*
Assign an index (rank) to every node in the stack
WHY: instead of comparing raw values, use algorithm to ranks it (-47, 3, 99)-->(0, 1, 2, ...)
simpler, avoid negatives edge cases
use bubble sort method.
a = act as assigning index
b = move to compare each with a and reset every round
*/

static void	assign_indexes(t_stack *stack)
{
	t_stack	*a;
	t_stack	*b;
	int		idx;
	
	a = stack;
	while (a)
	{
		b = stack;
		idx = 0;
		while (b)
		{
			if (b->val < a->val)
				idx++;
			b = b->next;
		}
		a->index = idx;
		a = a->next;
	}
}
