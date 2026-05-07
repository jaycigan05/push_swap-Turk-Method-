/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 11:24:13 by jagan             #+#    #+#             */
/*   Updated: 2026/05/07 13:33:19 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
PUSH = move the top of src to top of dst.
Steps:
Save the top of node src
detach it (src now point to second node)
put it on the top dst
a = [3,2,1] b = [5,4]
a = [2,1] b = [3,5,4]
*/

static void push(t_stack **dst, t_stack **src)
{
	t_stack *node;
	
	if (!src || !*src)
		return ;
	node = *src;
	*src = (*src)->next;
	node->next = *dst;
	*dst = node;
}

/*
pa = push the top of B onto A, print "pa"
*/

void	pa(t_stack **a, t_stack **b)
{
	push(a,b);
	write(1, "pa\n", 3);
}

void	pb(t_stack **a, t_stack **b)
{
	push(b,a);
	write(1, "pb\n", 3);
}