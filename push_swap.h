/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:26:04 by jagan             #+#    #+#             */
/*   Updated: 2026/05/02 13:03:46 by jagan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>

/*
The stack node. I use a singly linked list.
val = the actual integer value
index = its sorted rank (0,1,2,3,4...)
Assign the index after parsing (inout, error_msg) makes algo math easy
next = pointer to the node below it in the stack
*/

typedef struct s_stack
{
	int				val;
	int				index;
	struct s_stack	*next;
}	t_stack;

// stack_utils.c
t_stack	*ft_stacknew(int val);
void	ft_stackadd_top(t_stack **stack, t_stack *node);
int		ft_stacksize(t_stack *stack);
t_stack	*ft_stacklast(t_stack *stack);
void	ft_free(t_stack **stack);

// stack_init.c
t_stack	*init_stack_a(int argc, char **argv);

// utils.c
long	ft_atol(const char *str);
int		is_valid_arg(char *str);
int		has_duplicate(t_stack *stack, int val);
int		is_sorted(t_stack *stack);
int		ft_min_index(t_stack *stack);

// error.c
void	ft_error(t_stack **a);

// ops_swap.c
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);

// ops_push.c
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);

// ops_rotate.c
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

// sort_small.c
void	sort_2(t_stack **a);
void	sort_3(t_stack **a);
void	sort_5(t_stack **a, t_stack **b);

// sort_big.c
void	sort_big(t_stack **a, t_stack **b);

#endif
