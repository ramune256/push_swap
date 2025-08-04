/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:41:52 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/04 17:58:21 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_node	*node_at(t_stack *s, int idx)
{
	t_node	*cur;

	cur = s->top;
	while (idx-- && cur)
		cur = cur->next;
	return (cur);
}

int	target_idx_b(t_stack *b, int value)
{
	int		i;
	t_node	*cur;
	t_node	*next;

	if (b->size < 2)
		return (0);
	i = 0;
	cur = b->top;
	while (i < b->size)
	{
		if (cur->next)
			next = cur->next;
		else
			next = b->top;
		if (cur->value >= value && value >= next->value)
			return (i + 1);
		cur = cur->next;
		i++;
	}
	return (0);
}

int	target_idx_a(t_stack *a, int value)
{
	int		i;
	t_node	*cur;
	t_node	*next;

	if (a->size < 2)
		return (0);
	i = 0;
	cur = a->top;
	while (i < a->size)
	{
		if (cur->next)
			next = cur->next;
		else
			next = a->top;
		if (cur->value <= value && value <= next->value)
			return (i + 1);
		cur = cur->next;
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
		tmp.idx_b = target_idx_b(b, node_at(a, i)->value);
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
		tmp.idx_a = target_idx_a(a, node_at(b, i)->value);
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
	int	top;
	int	mid;
	int	bot;

	while (!(a->top->value < a->top->next->value \
		&& a->top->next->value < a->top->next->next->value))
	{
		top = a->top->value;
		mid = a->top->next->value;
		bot = a->top->next->next->value;
		if (top > mid && mid < bot && top < bot)
			sa(a);
		else if (top > mid && mid > bot)
		{
			sa(a);
			rra(a);
		}
		else if (top > mid && mid < bot && top > bot)
			ra(a);
		else if (top < mid && mid > bot && top < bot)
		{
			sa(a);
			ra(a);
		}
		else if (top < mid && mid > bot && top > bot)
			rra(a);
	}
}

void	execute_move(t_stack *a, t_stack *b, t_cost *move)
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
	if (b->top->value < b->top->next->value)
		sb(b);
	while (a->size > 3)
	{
		move = best_move_to_b(a, b);
		execute_move(a, b, &move);
		pb(a, b);
	}
	sort_three(a);
	while (b->size > 0)
	{
		move = best_move_to_a(a, b);
		execute_move(a, b, &move);
		pa(a, b);
	}
	finalize_stack(a);
}
