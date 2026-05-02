/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 12:57:37 by jagan             #+#    #+#             */
/*   Updated: 2026/05/02 15:58:31 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Create a brand-new stack node with a given value.
malloc one node, set val, index starts at 0, 
next is NULL. (point to nothing at first)
Returns NULL if malloc fails.
** dont need to check if !stack as node is new
*/

t_stack	*ft_stacknew(int val)
{
	t_stack	*node;

	node = malloc(sizeof(t_stack));
	if (!node)
		return (NULL);
	node->val = val;
	node->index = 0;
	node->next = NULL;
	return (node);
}

/*
Add a node to the TOP of the stack
The new node points to previous node,
** check if stack and node is available
(think like a plate, new plate on the top and old plate at the bottom)
*/

// always remember:
// *stack (head);
// **stack is its address

// want to change an `int`, Pass `int *`
// want to change a pointer (t_stack *)? Pass (t_stack **)
// want to change a double pointer? Pass (t_stack ***)

void	ft_stackadd_top(t_stack **stack, t_stack *node)
{
	if (!stack || !node)
		return ;
	node->next = *stack;
	*stack = node;
}

/*
counthow many nodes are in the stack
walk from top to bottom
(access to next)
*/

int	ft_stacksize(t_stack *stack)
{
	int	count;

	count = 0;
	while (stack)
	{
		count++;
		stack = stack->next;
	}
	return (count);
}

/*
Return a pointer to the LAST node (The bottom of the stack)
used by rotate operations
*/

t_stack	*ft_stacklast(t_stack *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

/*
Free the entire stack from top to bottom (free head first)
always NULL the pointer after freeing, 
avoid dangling pointers (hold an address but has been freed)
** remember if the head is null (!*stack), which will lead to
crash when tmp = (*stack)->next
*/

void	ft_free(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack || !*stack)
		return ;
	while (*stack)
	{
		tmp = (*stack)->next;
		free(*stack);
		*stack = tmp;
	}
	*stack = NULL;
}
