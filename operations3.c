/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:58:25 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/29 14:18:23 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void rr(t_stack *stack_a, t_stack *stack_b)
{
    rotate(stack_a);
    rotate(stack_b);
    write(1, "rr\n", 3);
}

void rrr(t_stack *stack_a, t_stack *stack_b)
{
    reverse_rotate(stack_a);
    reverse_rotate(stack_b);
    write(1, "rrr\n", 4);
}
