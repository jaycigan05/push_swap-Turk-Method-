/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:27:48 by jagan             #+#    #+#             */
/*   Updated: 2026/05/09 18:03:12 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_2(t_stack **stack)
{
	if (!stack || !*stack || !(*stack)->next)
		return ;
	if ((*stack)->index > (*stack)->next->index)
		sa(stack);
}

static void	sort_3_cases(t_stack **stack, t_stack *a, t_stack *b, t_stack *c)
{
	if (a->index < b->index && b->index > c->index && a->index < c->index)
	{
		rra(stack);
		sa(stack);
	}
	else if (a->index > b->index && b->index < c->index && a->index < c->index)
		sa(stack);
	else if (a->index < b->index && b->index > c->index && a->index > c->index)
		rra(stack);
	else if (a->index > b->index && b->index < c->index && a->index > c->index)
		ra(stack);
	else if (a->index > b->index && b->index > c->index && a->index > c->index)
	{
		sa(stack);
		rra(stack);
	}
}

void	sort_3(t_stack **stack)
{
	t_stack	*a;
	t_stack	*b;
	t_stack	*c;

	if (!stack || !*stack || !(*stack)->next)
		return ;
	a = *stack;
	b = a->next;
	c = b->next;
	if (a->index < b->index && b->index < c->index)
		return ;
	sort_3_cases(stack, a, b, c);
}

/*
rotate A until the node with target_index is at the top
*/
static void	rotate_to_top(t_stack **a, int target_index)
{
	while ((*a)->index != target_index)
		ra(a);
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
