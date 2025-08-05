/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:51:05 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/05 20:20:52 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack		*stack_a;
	t_stack		*stack_b;

	if (argc < 2)
		exit(1);
	stack_a = init_stack();
	if (!stack_a)
		error_exit(NULL, NULL);
	stack_b = init_stack();
	if (!stack_b)
		error_exit(stack_a, NULL);
	parse_args(argc, argv, stack_a, stack_b);

	// // デバッグ用
	// t_node		*tmp=stack_a->top;
	// while (tmp)
	// {
	// 	ft_printf("d\n", tmp->value);
	// 	tmp = tmp->next;
	// }

	turk_sort(stack_a, stack_b);
	free_stack(stack_a);
	free_stack(stack_b);
	return (0);
}
