/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jagan <jagan@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 19:26:04 by jagan             #+#    #+#             */
/*   Updated: 2026/05/21 11:15:47 by jagan            ###   ########.fr       */
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

// stack_utils.c//
t_stack	*ft_stacknew(int val);
void	ft_stackadd_top(t_stack **stack, t_stack *node);
int		ft_stacksize(t_stack *stack);
t_stack	*ft_stacklast(t_stack *stack);
void	ft_free(t_stack **stack);

// stack_init.c//
void	ft_error(t_stack **a);
t_stack	*init_stack_a(int argc, char **argv);

// utils.c//
long	ft_atol(const char *str);
int		is_valid_arg(char *str);
int		has_duplicate(t_stack *stack, int val);
int		is_sorted(t_stack *stack);
int		ft_min_index(t_stack *stack);

// ops_swap.c//
void	sa(t_stack **a);
void	sb(t_stack **b);
void	ss(t_stack **a, t_stack **b);

// ops_push.c//
void	pa(t_stack **a, t_stack **b);
void	pb(t_stack **a, t_stack **b);

// ops_rotate.c//
void	ra(t_stack **a);
void	rb(t_stack **b);
void	rr(t_stack **a, t_stack **b);

// ops_reverse_rotate.c//
void	rra(t_stack **a);
void	rrb(t_stack **b);
void	rrr(t_stack **a, t_stack **b);

// sort_small.c//
void	sort_2(t_stack **a);
void	sort_3(t_stack **a);
void	sort_4(t_stack **a, t_stack **b);
void	sort_5(t_stack **a, t_stack **b);

// sb_calc_cost.c//
int		cost_to_top(t_stack *stack, int target_index);
int		calc_cost(int cb, int ca);
int		find_cheapest(t_stack *a, t_stack *b);

// sb_find_target.c//
int		ft_abs(int n);
void	find_target_small_case(int *target, t_stack *a, int *best);
int		find_target(t_stack *a, int b_index);

// sort_big.c//
void	sort_big(t_stack **a, t_stack **b);

// ft_split.c//
char	**ft_split_space(char *s);
void	ft_free_split(char **split);

#endif
