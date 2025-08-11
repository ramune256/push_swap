/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_quickselect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/11 16:46:37 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 16:47:08 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(int *arr, int low, int high)
{
	int	pivot_value;
	int	i;
	int	j;

	pivot_value = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] < pivot_value)
		{
			i++;
			swap_int(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_int(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int	quickselect(int *arr, int low, int high, int k)
{
	int	pivot_index;

	if (low <= high)
	{
		pivot_index = partition(arr, low, high);
		if (pivot_index == k)
			return (arr[pivot_index]);
		else if (pivot_index > k)
			return (quickselect(arr, low, pivot_index - 1, k));
		else
			return (quickselect(arr, pivot_index + 1, high, k));
	}
	return (-1);
}

int	find_pivot(t_stack *a)
{
	t_node	*current;
	int		*arr;
	int		size;
	int		pivot;
	int		i;

	size = a->size;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (-1);
	current = a->top;
	i = 0;
	while (i < size)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	pivot = quickselect(arr, 0, size - 1, size / 2);
	free(arr);
	return (pivot);
}
