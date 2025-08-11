/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:43:10 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 20:17:38 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_five(t_stack *a, t_stack *b)
{
	int	min_index;
	int	count;

	min_index = find_min(a);
	if (min_index <= a->size / 2)
	{
		while (min_index--)
			ra(a);
	}
	else
	{
		count = a->size - min_index;
		while (count--)
			rra(a);
	}
	if (is_sorted(a))
		return ;
	pb(a, b);
	sort_four(a, b);
	pa(a, b);
}

void	sort_four(t_stack *a, t_stack *b)
{
	int	min_index;
	int	count;

	min_index = find_min(a);
	if (min_index <= a->size / 2)
	{
		while (min_index--)
			ra(a);
	}
	else
	{
		count = a->size - min_index;
		while (count--)
			rra(a);
	}
	if (is_sorted(a))
		return ;
	pb(a, b);
	sort_three(a);
	pa(a, b);
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
	first = a->top->value;
	second = a->top->next->value;
	if (first > second)
		sa(a);
}

void	a_piece_of_cake(t_stack *a, t_stack *b)
{
	if (a->size == 2 && (a->top->value) > (a->top->next->value))
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
	else if (a->size == 5)
		sort_five(a, b);
}
