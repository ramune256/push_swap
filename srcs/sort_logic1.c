/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_logic1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:57:40 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 20:17:20 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	get_better_way(t_cost *tmp)
{
	if (tmp->cost_a * tmp->cost_b >= 0)
	{
		if (ft_abs(tmp->cost_a) > ft_abs(tmp->cost_b))
			tmp->total = ft_abs(tmp->cost_a);
		else
			tmp->total = ft_abs(tmp->cost_b);
	}
	else
		tmp->total = ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b);
}

void	get_rough_cost(t_stack *a, t_stack *b, t_cost *tmp)
{
	if (tmp->idx_a <= a->size / 2)
		tmp->cost_a = tmp->idx_a;
	else
		tmp->cost_a = tmp->idx_a - a->size;
	if (tmp->idx_b <= b->size / 2)
		tmp->cost_b = tmp->idx_b;
	else
		tmp->cost_b = tmp->idx_b - b->size;
}

int	find_insert_position(t_stack *stack, int to_insert, char stackname)
{
	int		i;
	t_node	*current;
	t_node	*next;

	i = 0;
	current = stack->top;
	while (i < stack->size)
	{
		next = current->next;
		if (!next)
			next = stack->top;
		if (stackname == 'a' \
				&& (current->value < to_insert) && (to_insert < next->value))
			return (i + 1);
		if (stackname == 'b' \
				&& (current->value > to_insert) && (to_insert > next->value))
			return (i + 1);
		current = next;
		i++;
	}
	if (stackname == 'a')
		return (find_min(stack));
	else
		return (find_max(stack));
}

t_cost	best_move_to_a(t_stack *a, t_stack *b)
{
	t_cost	best;
	t_cost	tmp;
	int		i;

	best.total = 2147483647;
	i = 0;
	while (i < b->size)
	{
		tmp.idx_b = i;
		tmp.idx_a = find_insert_position(a, node_at(i, b)->value, 'a');
		get_rough_cost(a, b, &tmp);
		get_better_way(&tmp);
		if (tmp.total < best.total)
			best = tmp;
		i++;
	}
	return (best);
}
