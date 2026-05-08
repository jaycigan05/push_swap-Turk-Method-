/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops_swap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:34:57 by jagan             #+#    #+#             */
/*   Updated: 2026/05/08 09:46:16 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
SWAP = exchange the value of the top two nodes
WHY swap value and index, why not pointer?
value and index, you may store it in a temporary variable, 
if changing pointer, which means will touch more than 3 pointers.
[2] -> [1] -> [3]
becomes....
[1] -> [2] -> [3] (top 2 changed)
*/

static void	swap(t_stack *stack)
{
	int	tmp_val;
	int	tmp_idx;

	if (!stack || !(stack->next))
		return ;
	tmp_val = stack->val;
	tmp_idx = stack->index;
	stack->val = stack->next->val;
	stack->index = stack->next->index;
	stack->next->val = tmp_val;
	stack->next->index = tmp_idx;
}

/*
sa = swap top 2 elements of stack A, print "sa"
*/
void	sa(t_stack **a)
{
	swap(*a);
	write(1, "sa\n", 3);
}

/*
sb = swap top 2 elements of stack B, print "sb"
*/
void	sb(t_stack **b)
{
	swap(*b);
	write(1, "sb\n", 3);
}

/*
ss = do sa and sb at the same time
*/

void	ss(t_stack **a, t_stack **b)
{
	swap(*a);
	swap(*b);
	write(1, "ss\n", 3);
}

/*
a         = the address of the pointer variable   (0x30 or 0x50)
*a        = the pointer variable itself           → which node is head
**a       = the node the pointer points to        → val, index, next
(*a)->val = a field inside that node

**Add * for each level you want to be able to modify. 
If you only read — * is enough. 
** If you need to change the variable itself from inside a function 
—-> add one more *.
*/
