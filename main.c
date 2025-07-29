/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:51:05 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/29 23:08:31 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int main(int argc, char **argv)
{
    t_stack *stack_a;
    t_stack *stack_b;

    if (argc < 2)
        exit(1);
	stack_a = init_stack();
	stack_b = init_stack();
    parse_args(argv, &stack_a);

    // // スタックの内容を確認するための出力（デバッグ用）
    // t_node *tmp = stack_a->top;
    // while (tmp) {
    //     ft_printf("%d\n", tmp->value);
    //     tmp = tmp->next;
    // }

    free_stack(stack_a);
    free_stack(stack_b);
    return (0);
}
