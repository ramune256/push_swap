/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:53:29 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/29 14:18:03 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void ra(t_stack *stack_a)
{
    rotate(stack_a);
    write(1, "ra\n", 3);
}

void rb(t_stack *stack_b)
{
    rotate(stack_b);
    write(1, "rb\n", 3);
}

void rra(t_stack *stack_a)
{
    reverse_rotate(stack_a);
    write(1, "rra\n", 4);
}

void rrb(t_stack *stack_b)
{
    reverse_rotate(stack_b);
    write(1, "rrb\n", 4);
}
