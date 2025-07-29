/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 14:16:42 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/29 22:53:16 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	add_node(t_stack *stack, int value)
{
    t_node *new_node;

	new_node = ft_lstnew(value);
    if (!new_node)
        error_exit();
    ft_lstadd_front(&(stack->top), new_node);
    stack->size++;
}

int	del_node(t_stack *stack)
{
    t_node	*top_node;
	int		value;

    if (stack->size == 0)
        return;
	top_node = stack->top;
	value = top_node->value;
    stack->top = top_node->next;
    free(top_node);
    stack->size--;
    return (value);
}

void swap(t_stack *stack)
{
    int first;
    int second;

    if (stack->size < 2)
        return;
    first = del_node(stack);
    second = del_node(stack);
    add_node(stack, first);
    add_node(stack, second);
}

void rotate(t_stack *stack)
{
    t_node  *old_top;

    if (stack->size < 2)
        return;
    old_top = stack->top;
    stack->top = stack->top->next;
    old_top->next = NULL;
    ft_lstadd_back(&(stack->top), old_top);
}

void reverse_rotate(t_stack *stack)
{
    t_node *tail;
    t_node *prev;

    if (stack->size < 2)
        return;
    tail = ft_lstlast(stack->top);
    prev = stack->top;
    while (prev->next != tail)
        prev = prev->next;
    prev->next = NULL;
    ft_lstadd_front(&(stack->top), tail);
}
