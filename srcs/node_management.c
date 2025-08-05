/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:16:42 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/05 20:07:12 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#include "push_swap.h"

void	add_node(t_stack *stack, int value)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
	{
		write(2, "Error\n", 6);
		return;
	}
	new_node->value = value;
	new_node->next = stack->top;
	stack->top = new_node;
	stack->size++;
}

int	del_node(t_stack *stack)
{
	t_node	*top_node;
	int		value;

	if (stack->size == 0)
		return (0);
	top_node = stack->top;
	value = top_node->value;
	stack->top = top_node->next;
	free(top_node);
	stack->size--;
	return (value);
}

void	swap(t_stack *stack)
{
	int	first;
	int	second;

	if (stack->size < 2)
		return;
	first = del_node(stack);
	second = del_node(stack);
	add_node(stack, first);
	add_node(stack, second);
}

void	rotate(t_stack *stack)
{
	t_node	*old_top;
	t_node	*tail;

	if (stack->size < 2)
		return;
	old_top = stack->top;
	stack->top = stack->top->next;
	old_top->next = NULL;
	tail = stack->top;
	while (tail && tail->next)
		tail = tail->next;
	tail->next = old_top;
}

void	reverse_rotate(t_stack *stack)
{
	t_node	*tail;
	t_node	*prev;

	if (stack->size < 2)
		return;
	tail = stack->top;
	while (tail->next)
	{
		prev = tail;
		tail = tail->next;
	}
	prev->next = NULL;
	tail->next = stack->top;
	stack->top = tail;
}
