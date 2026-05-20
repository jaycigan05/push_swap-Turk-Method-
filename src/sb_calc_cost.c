/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_calc_cost.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 10:09:02 by jagan             #+#    #+#             */
/*   Updated: 2026/05/11 10:09:39 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Count how many rotation need to bring the node
with target_index to the top of stack

count its position first
count the size of current stack (its own stack)

if it's first half, rotate forward (ra/rb)-> positive cost
if it's second half, reverse rotate (rra/rrb) -> negative cost
*/
int	cost_to_top(t_stack *stack, int target_index)
{
	int	pos;
	int	size;

	pos = 0;
	size = ft_stacksize(stack);
	while (stack->index != target_index)
	{
		pos++;
		stack = stack->next;
	}
	if (pos <= size / 2)
		return (pos);
	return (-(size - pos));
}

/*
calculate total cost for one B element

Same direction (both +, both -)
rr/rrr combines moves -> pay only for the larger one

Different direction:
No combination possible -> pay for both (sum of absolute)
*/
int	calc_cost(int cb, int ca)
{
	if ((cb >= 0 && ca >= 0) || (cb < 0 && ca < 0))
	{
		if (ft_abs(cb) > ft_abs(ca))
			return (ft_abs(cb));
		return (ft_abs(ca));
	}
	return (ft_abs(cb) + ft_abs(ca));
}

/*
Find the cheapest element in B and push next.

For each element in B:
- find its taget position in A
- calculate cost_b (rotation needed in B)
- calculate cost_a (rotation needed in A)
- total cost via calc_cost
- track lowest cost element

Return the index of the cheapest B element
*/
int	find_cheapest(t_stack *a, t_stack *b)
{
	t_stack	*tmp;
	int		cb;
	int		ca;
	int		best_cost;
	int		best_index;

	tmp = b;
	best_cost = 2147483647;
	best_index = tmp->index;
	while (tmp)
	{
		cb = cost_to_top(b, tmp->index);
		ca = cost_to_top(a, find_target(a, tmp->index));
		if (calc_cost(cb, ca) < best_cost)
		{
			best_cost = calc_cost(cb, ca);
			best_index = tmp->index;
		}
		tmp = tmp->next;
	}
	return (best_index);
}
