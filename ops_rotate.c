/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_rotate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 13:39:09 by jagan             #+#    #+#             */
/*   Updated: 2026/05/10 08:59:42 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
ROTATE: Shift all the elements up by 1
Top element goes to the bottom.
[1], [2], [3], [NULL] --> [2],[3],[1],[NULL]
Step:
-save the top of node
-stack start at the second
-go to the last node, attach the save top there
*/

static void	rotate(t_stack **stack)
{
	t_stack	*top;
	t_stack	*last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	top = *stack;
	*stack = (*stack)->next;
	top->next = NULL;
	last = ft_stacklast(*stack);
	last->next = top;
}

/*
ra = rotate A up, print "ra"
*/
void	ra(t_stack **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

/*
rb = rotate B up, print "rb"
*/

void	rb(t_stack **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

/*
rr = rotate A and B at the same time
*/
void	rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}
