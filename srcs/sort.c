/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:41:52 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 20:14:58 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	finalize_stack(t_stack *a)
{
	int	min_index;

	min_index = find_min(a);
	if (min_index <= a->size / 2)
	{
		while (min_index--)
			ra(a);
	}
	else
	{
		min_index = a->size - min_index;
		while (min_index--)
			rra(a);
	}
}

void	push_back_to_a(t_stack *a, t_stack *b)
{
	t_cost	move;

	while (b->size > 0)
	{
		move = best_move_to_a(a, b);
		rotate_stacks(a, b, &move);
		pa(a, b);
	}
}

void	push_non_lis_to_b(t_stack *a, t_stack *b, int lis)
{
	int	pivot;
	int	to_push;

	pivot = find_pivot(a);
	if (pivot == -1)
		error_exit(a, b);
	to_push = a->size - lis;
	while (to_push > 0)
	{
		if (a->top->lis_flag == 0)
		{
			pb(a, b);
			to_push--;
			if (b->top->value <= pivot && b->size > 1)
				rb(b);
		}
		else
			ra(a);
	}
}

int	search_lis(t_stack *a, t_stack *b)
{
	int	*nums;
	int	lis;

	nums = stack_to_int_array_2x(a, b);
	lis = lis_manage(nums, a);
	free(nums);
	if (lis == -1)
		error_exit(a, b);
	return (lis);
}

void	my_sort(t_stack *a, t_stack *b)
{
	int		lis;

	if (a->size <= 5)
	{
		a_piece_of_cake(a, b);
		return ;
	}
	lis = search_lis(a, b);
	if (lis == a->size)
	{
		finalize_stack(a);
		return ;
	}
	push_non_lis_to_b(a, b, lis);
	push_back_to_a(a, b);
	finalize_stack(a);
}
