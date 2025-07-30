/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 22:55:28 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/30 13:27:30 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    error_exit(void)
{
    write(2, "Error\n", 6);
    exit(1);
}

void	free_2d_array(char **array)
{
	int i;

	if (!array)
		return;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void    add_numbers(t_stack **stack_a, char **nums)
{
    int i;

    i = 0;
	while (nums[i])
	{
        add_node(*stack_a, ft_atoi(nums[i]));
		i++;
	}
}

void    parse_args(char **argv, t_stack **stack_a)
{
    char    **nums;

    if (ft_strchr(argv[1], ' '))
    {
        nums = ft_split(argv[1], ' ');
        if (!nums)
        {
            free_stack(*stack_a);
            error_exit();
        }
        error_finder(nums);
        add_numbers(stack_a, nums);
        free_2d_array(nums);
    }
    else
    {
        error_finder(argv + 1);
        add_numbers(stack_a, (argv + 1));
    }
}
