/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:42:00 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 16:42:39 by shunwata         ###   ########.fr       */
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

t_node	*node_at(int index, t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (index-- && current)
		current = current->next;
	return (current);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack->top || !stack->top->next)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if ((current->value) > (current->next->value))
			return (0);
		current = current->next;
	}
	return (1);
}

int	find_min(t_stack *stack)
{
	int		min_value;
	int		min_index;
	int		i;
	t_node	*current;

	if (stack->size == 0)
		return (0);
	min_value = stack->top->value;
	min_index = 0;
	i = 0;
	current = stack->top;
	while (i < stack->size)
	{
		if (current->value < min_value)
		{
			min_value = current->value;
			min_index = i;
		}
		current = current->next;
		i++;
	}
	return (min_index);
}

int	find_max(t_stack *stack)
{
	int		max_value;
	int		max_index;
	int		i;
	t_node	*current;

	if (stack->size == 0)
		return (0);
	max_value = stack->top->value;
	max_index = 0;
	i = 0;
	current = stack->top;
	while (i < stack->size)
	{
		if (current->value > max_value)
		{
			max_value = current->value;
			max_index = i;
		}
		current = current->next;
		i++;
	}
	return (max_index);
}
