/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 10:27:48 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 00:00:00 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_error(t_stack **a)
{
	ft_free(a);
	write(2, "Error\n", 6);
	exit(1);
}

void	assign_indexes(t_stack *stack)
{
	t_stack	*a;
	t_stack	*b;
	int		idx;

	a = stack;
	while (a)
	{
		b = stack;
		idx = 0;
		while (b)
		{
			if (b->val < a->val)
				idx++;
			b = b->next;
		}
		a->index = idx;
		a = a->next;
	}
}

int	parse_one(char *arg, t_stack **a)
{
	long	num;

	if (!is_valid_arg(arg))
		ft_error(a);
	num = ft_atol(arg);
	if (num > 2147483647 || num < -2147483648)
		ft_error(a);
	return ((int)num);
}

/*
** Add a single validated token to the bottom of the stack.
** Checks for duplicates before adding.
*/
void	add_token(char *token, t_stack **a)
{
	t_stack	*node;
	t_stack	*last;

	node = ft_stacknew(parse_one(token, a));
	if (has_duplicate(*a, node->val))
	{
		free(node);
		ft_error(a);
	}
	if (!*a)
		*a = node;
	else
	{
		last = ft_stacklast(*a);
		last->next = node;
	}
}

/*
** Process one argv string.
** Splits by spaces so both "3 1 2" and 3 1 2 work.
** Empty or whitespace-only strings trigger error.
*/
void	process_arg(char *arg, t_stack **a)
{
	char	**tokens;
	int		i;

	tokens = ft_split_space(arg);
	if (!tokens || !tokens[0])
	{
		ft_free_split(tokens);
		ft_error(a);
	}
	i = 0;
	while (tokens[i])
	{
		add_token(tokens[i], a);
		i++;
	}
	ft_free_split(tokens);
}
