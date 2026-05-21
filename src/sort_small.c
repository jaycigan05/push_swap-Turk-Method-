/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_small.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:27:48 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 12:06:53 by jagan            ###   ########.fr       */
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

	if (!stack || !*stack || !(*stack)->next || !(*stack)->next->next)
		return ;
	a = *stack;
	b = a->next;
	c = b->next;
	if (a->index < b->index && b->index < c->index)
		return ;
	sort_3_cases(stack, a, b, c);
}
