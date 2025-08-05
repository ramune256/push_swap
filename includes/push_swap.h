/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:54:10 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/05 20:22:17 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	push_swap_h
# define push_swap_h

# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct	s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct	s_cost
{
	int		idx_a;
	int		idx_b;
	int		cost_a;
	int		cost_b;
	int		total;
}	t_cost;

int		is_valid_int(const char *str);
int		is_positive(const char *str);
int		is_numeric(const char *str);
void	error_finder(char **nums, t_stack *stack_a, t_stack *stack_b);

void	add_node(t_stack *stack, int value);
int		del_node(t_stack *stack);
void	swap(t_stack *stack);
void	rotate(t_stack *stack);
void	reverse_rotate(t_stack *stack);

void	sa(t_stack *stack_a);
void	sb(t_stack *stack_b);
void	ss(t_stack *stack_a, t_stack *stack_b);
void	pa(t_stack *stack_a, t_stack *stack_b);
void	pb(t_stack *stack_a, t_stack *stack_b);

void	ra(t_stack *stack_a);
void	rb(t_stack *stack_b);
void	rra(t_stack *stack_a);
void	rrb(t_stack *stack_b);

void	rr(t_stack *stack_a, t_stack *stack_b);
void	rrr(t_stack *stack_a, t_stack *stack_b);

void	error_exit(t_stack *stack_a, t_stack *stack_b);
void	free_2d_array(char **array);
void	add_numbers(t_stack *stack_a, char **nums);
void	parse_args(int argc, char **argv, t_stack *stack_a, t_stack *stack_b);

int		ft_abs(int n);
int		value_of_node(int index, t_stack *stack);
int		find_insert_position(t_stack *stack, int to_insert, char stackname);
void	get_better_way(t_cost *tmp);
void	get_rough_cost(t_stack *a, t_stack *b, t_cost *tmp);
t_cost	best_move_to_b(t_stack *a, t_stack *b);
t_cost	best_move_to_a(t_stack *a, t_stack *b);
void	sort_three(t_stack *a);
void	a_piece_of_cake(t_stack *a);
void	rotate_a(t_stack *a, t_cost *move);
void	rotate_b(t_stack *b, t_cost *move);
void	rotate_stacks(t_stack *a, t_stack *b, t_cost *move);
void	finalize_stack(t_stack *a);
void	turk_sort(t_stack *a, t_stack *stack_b);

t_stack	*init_stack(void);
void	free_stack(t_stack *stack);

#endif
