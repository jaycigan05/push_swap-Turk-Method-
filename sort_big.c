/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:09:28 by jagan             #+#    #+#             */
/*   Updated: 2026/05/11 08:51:08 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Return the absolute value of n
used for cost calculation, direction does not matter
only the number of moves 

** used in @find_cheapest
*/
static int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/*
spilted function from @find_target
*/
static void	find_target_small_case(int *target, t_stack *a, int *best)
{
	t_stack	*tmp;

	if (*target == -1)
	{
		tmp = a;
		while (tmp)
		{
			if (tmp->index > *best)
				*best = tmp->index;
			tmp = tmp->next;
		}
		*target = *best;
	}
}

/**
Find where in A a given B element (b_index) should be inderted

We want to take the largest element in A but still smaller than b_index
The element should end up just BELOW the inserted value after pa.

eg: A = [0, 3, 4, 7], b_index = [5]
target = 4 (largest in A thst is still < 5)

**if b_index is smaller everything in A, 
target the maximum in A

**target = used to store value
**best = the current best result
*/
static int	find_target(t_stack *a, int b_index)
{
	int		target;
	int		best;
	t_stack	*tmp;

	target = -1;
	best = -1;
	tmp = a;
	while (tmp)
	{
		if (tmp->index < b_index && tmp->index > best)
		{
			best = tmp->index;
			target = tmp->index;
		}
		tmp = tmp->next;
	}
	find_target_small_case(&target, a, &best);
	return (target);
}

/*
Count how many rotation need to bring the node
with target_index to the top of stack

count its position first
count the size of current stack (its own stack)

if it's first half, rotate forward (ra/rb)-> positive cost
if it's second half, reverse rotate (rra/rrb) -> negative cost
*/
static int	cost_to_top(t_stack *stack, int target_index)
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
static int	calc_cost(int cb, int ca)
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
static int	find_cheapest(t_stack *a, t_stack *b)
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

/*
Execute the cheapest move.
Rotate A and B toward correct positions, then pa.

same direction -> rr or rrr (saves moves)
different direction -> rotate each independently	
*/
static void	do_move(t_stack **a, t_stack **b, int b_idx)
{
	int	cb;
	int	ca;

	cb = cost_to_top(*b, b_idx);
	ca = cost_to_top(*a, find_target(*a, b_idx));
	while (cb > 0 && ca > 0)
	{
		rr(a, b);
		cb--;
		ca--;
	}
	while (cb < 0 && ca < 0)
	{
		rrr(a, b);
		cb++;
		ca++;
	}
	while (cb > 0)
	{
		rb(b);
		cb--;
	}
	while (cb < 0)
	{
		rrb(b);
		cb++;
	}
	while (ca > 0)
	{
		ra(a);
		ca--;
	}
	while (ca < 0)
	{
		rra(a);
		ca++;
	}
	pa(a, b);
}

/*
After all elements are in A, rotate so
the smallest index 0 should end up at the top
uses ra / rra to determine which is cheaper
*/
static void	rotate_min_top(t_stack **a)
{
	int	cost;

	cost = cost_to_top(*a, ft_min_index(*a));
	while (cost > 0)
	{
		ra(a);
		cost--;
	}
	while(cost < 0)
	{
		rra(a);
		cost++;
	}
}

/*
Main Turk algorithm:
Push all but 3 elements from A to B
Sort the 3 remaining in A with sort_3
While B has elements, find the cheapest, execute move
Rotate A so the minimum at the top
*/
void	sort_big(t_stack **a, t_stack **b)
{
	int	size;

	size = ft_stacksize(*a);
	while (size > 3)
	{
		pb(a, b);
		size--;
	}
	sort_3(a);
	while (*b)
		do_move(a, b, find_cheapest(*a, *b));
	rotate_min_to_top(a);
}