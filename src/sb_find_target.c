/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sb_find_target.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:44:47 by jagan             #+#    #+#             */
/*   Updated: 2026/05/11 10:08:13 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Return the absolute value of n
used for cost calculation, direction does not matter
only the number of moves 

** used in @find_cheapest
*/
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/*
spilted function from @find_target
*/
void	find_target_small_case(int *target, t_stack *a, int *best)
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
int	find_target(t_stack *a, int b_index)
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
