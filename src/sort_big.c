/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/09 18:09:28 by jagan             #+#    #+#             */
/*   Updated: 2026/05/11 10:22:57 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
splited function from @do_move
*/
static void	do_move_different_path(int *ca, int *cb, t_stack **a, t_stack **b)
{
	while (*cb > 0)
	{
		rb(b);
		(*cb)--;
	}
	while (*cb < 0)
	{
		rrb(b);
		(*cb)++;
	}
	while (*ca > 0)
	{
		ra(a);
		(*ca)--;
	}
	while (*ca < 0)
	{
		rra(a);
		(*ca)++;
	}
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
	do_move_different_path(&ca, &cb, a, b);
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
	while (cost < 0)
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
	rotate_min_top(a);
}
