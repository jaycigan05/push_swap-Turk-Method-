/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init_stack.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 12:12:37 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 12:19:27 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
/*
** Build stack A from all command-line arguments.
** Each argv goes through ft_split_space so quoted strings
** like "3 1 2" are handled the same as separate args 3 1 2.
*/
t_stack	*init_stack_a(int argc, char **argv)
{
	t_stack	*a;
	int		i;

	a = NULL;
	i = 1;
	while (i < argc)
	{
		process_arg(argv[i], &a);
		i++;
	}
	assign_indexes(a);
	return (a);
}
