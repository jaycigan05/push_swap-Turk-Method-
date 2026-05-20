/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 09:01:56 by jagan             #+#    #+#             */
/*   Updated: 2026/05/11 09:40:36 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;
	int		size;

	if (argc < 2)
		return (0);
	a = init_stack_a(argc, argv);
	b = NULL;
	if (is_sorted(a))
	{
		ft_free(&a);
		return (0);
	}
	size = ft_stacksize(a);
	if (size == 2)
		sort_2(&a);
	else if (size == 3)
		sort_3(&a);
	else if (size <= 5)
		sort_5(&a, &b);
	else if (size > 5)
		sort_big(&a, &b);
	ft_free(&b);
	ft_free(&a);
	return (0);
}
