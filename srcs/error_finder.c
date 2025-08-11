/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_finder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:33:15 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/11 20:18:30 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_valid_int(const char *str)
{
	int		len;

	len = ft_strlen(str);
	if (*str == '-')
	{
		if (len > 11)
			return (0);
		if (len == 11 && ft_strncmp(str, "-214748364", 10) == 0 && \
				str[10] > '8')
			return (0);
	}
	else
	{
		if (len > 10)
			return (0);
		if (len == 10 && ft_strncmp(str, "214748364", 9) == 0 && \
				str[9] > '7')
			return (0);
	}
	return (1);
}

int	is_numeric(const char *str)
{
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	error_finder(char **nums, t_stack *stack_a, t_stack *stack_b)
{
	int		i;
	int		j;

	i = 0;
	while (nums[i])
	{
		if (!(is_numeric(nums[i]) && \
				is_valid_int(nums[i]) && \
				ft_strlen(nums[i])))
			error_exit(stack_a, stack_b);
		j = i + 1;
		while (nums[j])
		{
			if (ft_strncmp(nums[i], nums[j], 11) == 0)
				error_exit(stack_a, stack_b);
			j++;
		}
		i++;
	}
	if (i == 0)
		error_exit(stack_a, stack_b);
}
