/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:51:05 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/29 14:20:52 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;
	int		i;

	stack_a = init_stack();
	stack_b = init_stack();
	i = 0;
	while (i < argc)
	{
        add_node(stack_a, ft_atoi(argv[i]));
		i++;
	}

    // スタックの内容を確認するための出力（デバッグ用）
    t_node *current = stack_a->top;
    while (current) {
        ft_printf("%d\n", current->value);
        current = current->next;
    }

    free_stack(stack_a);
    free_stack(stack_b);
    return 0;
}
