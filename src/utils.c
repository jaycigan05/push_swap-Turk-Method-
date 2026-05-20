/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 12:34:26 by jagan             #+#    #+#             */
/*   Updated: 2026/05/03 13:57:00 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
convert a string to a long integer
LONG (not int) so we can detect values outside of range
handlle + || -
*/

long	ft_atol(const char *str)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

/*
check if a string is a valid integer argument
rules: 
optional leading '+' || '-';
followed by digits ONLY (no letter/ space)
return 1 if valid, 0 if not
**consider this case: if only input '+' ||'-' ONLY, return 0
*/

int	is_valid_arg(char *str)
{
	if (!str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

/*
check if a value ald exist in stack
walk through every node and compare val.
return 1 if dup. return 0 if not.
*/

int	has_duplicate(t_stack *stack, int val)
{
	while (stack)
	{
		if (stack->val == val)
			return (1);
		stack = stack->next;
	}
	return (0);
}

/*
check if stack is ald sorted in ascending order (top = smallest)
small -> big
return 1 if sorted, 0 if not
*/

int	is_sorted(t_stack *stack)
{
	while (stack)
	{
		if (stack->val > stack->next->val)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
find the node with lowest index in the stack
used at the end of sort_big to rotate the minimum to the top of A
return the index value of the minimum element
*/

int	ft_min_index(t_stack *stack)
{
	int	min;

	min = stack->index;
	while (stack)
	{
		if (stack->index < min)
			min = stack->index;
		stack = stack->next;
	}
	return (min);
}
