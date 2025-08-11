/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_logic2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:57:07 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 17:01:51 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate_b(t_stack *b, t_cost *move)
{
	while (move->cost_b > 0)
	{
		rb(b);
		move->cost_b--;
	}
	while (move->cost_b < 0)
	{
		rrb(b);
		move->cost_b++;
	}
}

void	rotate_a(t_stack *a, t_cost *move)
{
	while (move->cost_a > 0)
	{
		ra(a);
		move->cost_a--;
	}
	while (move->cost_a < 0)
	{
		rra(a);
		move->cost_a++;
	}
}

void	rotate_stacks(t_stack *a, t_stack *b, t_cost *move)
{
	while (move->cost_a > 0 && move->cost_b > 0)
	{
		rr(a, b);
		move->cost_a--;
		move->cost_b--;
	}
	while (move->cost_a < 0 && move->cost_b < 0)
	{
		rrr(a, b);
		move->cost_a++;
		move->cost_b++;
	}
	rotate_a(a, move);
	rotate_b(b, move);
}
