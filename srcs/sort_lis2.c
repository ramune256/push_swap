/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lis2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:45:37 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 16:49:28 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*stack_to_int_array_2x(t_stack *a, t_stack *b)
{
	int		*nums;
	t_node	*current;
	int		size;
	int		i;

	size = a->size;
	nums = malloc(sizeof(int) * size * 2);
	if (!nums)
		error_exit(a, b);
	current = a->top;
	i = 0;
	while (i < size)
	{
		nums[i] = current->value;
		nums[i + size] = current->value;
		current = current->next;
		i++;
	}
	return (nums);
}
