/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 09:44:47 by jagan             #+#    #+#             */
/*   Updated: 2026/05/05 11:09:57 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
Print "Error\n" to stderr; free stack and exit
when found non-integer/ out of range/ duplicate
** exit = stop immediately of the whole programme 
to prevent keep running
*/

void	ft_error(t_stack **a)
{
	ft_free(a);
	write(2, "Error\n", 6);
	exit(1);
}

/*
Assign an index (rank) to every node in the stack
WHY: instead of comparing raw values, use algorithm 
to ranks it (-47, 3, 99)-->(0, 1, 2, ...)
simpler, avoid negatives edge cases
use bubble sort method.
a = act as assigning index
b = move to compare each with a and reset every round
*/

static void	assign_indexes(t_stack *stack)
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

/*
Validate one argument: must be a valid integer in INT range
** int2,147,483,647 // long9,223,372,036,854,775,807
if invalid -- trigger to print error msg
return valid int number

**catch the return value when reuse the return value multiple times
*/

static int	parse_one(char *arg, t_stack **a)
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
Build stack A from command-line arguments
Process
- loop argv[1] to argv[argc-1]
- parse_one (is_valid_arg + check range)
- check duplicate
-add new node at the bottom of the stack
(argv[1] at the top, argv[argc-1] at the bottom)
- assign index after all is built

** add the the bottom (ft_stacklast + last->next = node)
make sure in order stack
*/

t_stack	*init_stack_a(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*node;
	t_stack	*last;
	int		i;

	i = 1;
	while (i < argc)
	{
		node = ft_stacknew(parse_one(argv[i], &a));
		if (has_duplicate(a, node->val))
		{
			free(node);
			ft_error(&a);
		}
		if (!a)
			a = node;
		else
		{
			last = ft_stacklast(a);
			last->next = node;
		}
		assign_indexes(a);
		return (a);
	}
}
