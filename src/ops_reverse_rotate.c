/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_reverse_rotate.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 12:19:44 by jagan             #+#    #+#             */
/*   Updated: 2026/05/11 10:45:54 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
REVERSE ROTATE: Shift all elements down by 1
Bottom element comes to the top.
(rra):
[1],[2],[3],[NULL] --> [3],[1],[2],[NULL]

Step:
- walk to the seond-to-last node (the one before the bottom)
- detach the last node(second_last->next = NULL)
- put the old node on the top (*stack = old_last)
*/
static void	reverse_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*second_last;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	last = ft_stacklast(*stack);
	second_last = *stack;
	while (second_last->next != last)
		second_last = second_last->next;
	second_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

/*
rra = reverse rotate A, print "rra"
*/
void	rra(t_stack **a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

/*
rrb = reverse rotate B, print "rrb"
*/
void	rrb(t_stack **b)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}

/*
rrr = reverse rotate both A and B, print "rrr"
*/
void	rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
}
