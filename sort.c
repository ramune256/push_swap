/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:41:52 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/04 21:32:20 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abs(int n)
{
	if (n == -2147483648)
		return (2147483647);
	if (n < 0)
		return (-n);
	return (n);
}

int	value_of_node(int index, t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (index-- && current)
		current = current->next;
	return (current->value);
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
		if (current->next)
			next = current->next;
		else
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
	return (0);
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

t_cost	best_move_to_b(t_stack *a, t_stack *b)
{
	t_cost	best;
	t_cost	tmp;
	int		i;

	best.total = 2147483647;
	i = 0;
	while (i < a->size)
	{
		tmp.idx_a = i;
		tmp.idx_b = find_insert_position(b, value_of_node(i, a), 'b');
		get_rough_cost(a, b, &tmp);
		get_better_way(&tmp);
		if (tmp.total < best.total)
			best = tmp;
		i++;
	}
	return (best);
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
		tmp.idx_a = find_insert_position(a, value_of_node(i, b), 'a');
		get_rough_cost(a, b, &tmp);
		get_better_way(&tmp);
		if (tmp.total < best.total)
			best = tmp;
		i++;
	}
	return (best);
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	if (first > second && first > third)
		ra(a);
	else if (second > first && second > third)
		rra(a);
	if (first > second)
		sa(a);
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

void	finalize_stack(t_stack *a)
{
	int		min_idx;
	int		i;
	t_node	*cur;
	int		min_val;

	min_idx = 0;
	i = 0;
	cur = a->top;
	min_val = cur->value;
	while (i < a->size)
	{
		if (cur->value < min_val)
		{
			min_val = cur->value;
			min_idx = i;
		}
		cur = cur->next;
		i++;
	}
	if (min_idx <= a->size / 2)
	{
		while (min_idx--)
			ra(a);
	}
	else
	{
		min_idx = a->size - min_idx;
		while (min_idx--)
			rra(a);
	}
}

void	a_piece_of_cake(t_stack *a)
{
	if (a->size == 2 && a->top->value > a->top->next->value)
		sa(a);
	else if (a->size == 3)
		sort_three(a);
}

void	turk_sort(t_stack *a, t_stack *b)
{
	t_cost	move;

	if (a->size <= 3)
	{
		a_piece_of_cake(a);
		return;
	}
	pb(a, b);
	pb(a, b);
	if ((b->top->value) < (b->top->next->value))
		sb(b);
	while (a->size > 3)
	{
		move = best_move_to_b(a, b);
		rotate_stacks(a, b, &move);
		pb(a, b);
	}
	sort_three(a);
	while (b->size > 0)
	{
		move = best_move_to_a(a, b);
		rotate_stacks(a, b, &move);
		pa(a, b);
	}
	finalize_stack(a);
}
