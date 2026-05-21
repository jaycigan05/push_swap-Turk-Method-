/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_fourfive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:07:15 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 12:18:35 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
rotate A until the node with target_index is at the top
*/
static void	rotate_to_top(t_stack **a, int target_index)
{
	int		size;
	int		pos;
	t_stack	*tmp;

	size = ft_stacksize(*a);
	pos = 0;
	tmp = *a;
	while (tmp->index != target_index)
	{
		pos++;
		tmp = tmp->next;
	}
	if (pos <= size / 2)
	{
		while ((*a)->index != target_index)
			ra(a);
	}
	else
	{
		while ((*a)->index != target_index)
			rra(a);
	}
}

void	sort_4(t_stack **a, t_stack **b)
{
	if (!a || !*a || !b)
		return ;
	rotate_to_top(a, ft_min_index(*a));
	pb(a, b);
	sort_3(a);
	pa(a, b);
}

void	sort_5(t_stack **a, t_stack **b)
{
	if (!a || !*a || !b)
		return ;
	rotate_to_top(a, 0);
	pb(a, b);
	rotate_to_top(a, 1);
	pb(a, b);
	sort_3(a);
	pa(a, b);
	pa(a, b);
}
