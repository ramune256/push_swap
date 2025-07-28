/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:51:05 by shunwata          #+#    #+#             */
/*   Updated: 2025/07/28 16:23:09 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

typedef struct s_node {
    int				value;
    struct s_node	*next;
} t_node;

typedef struct s_stack {
    t_node	*top;
    int		size;
} t_stack;

t_stack	*init_stack(void)
{
    t_stack *stack;

	stack = (t_stack *)malloc(sizeof(t_stack));
    if (!stack)
        exit(1);
    stack->top = NULL;
    stack->size = 0;
    return (stack);
}

void	push(t_stack *stack, int value)
{
    t_node *new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
    if (!new_node)
        exit(1);
    new_node->value = value;
    new_node->next = stack->top;
    stack->top = new_node;
    stack->size++;
}

int	pop(t_stack *stack)
{
    t_node	*top_node;
	int		value;

    if (stack->size == 0)
        exit(1);
	top_node = stack->top;
	value = stack->top->value;
    stack->top = top_node->next;
    free(top_node);
    stack->size--;
    return (value);
}

void	free_stack(t_stack *stack)
{
    while (stack->size > 0)
        pop(stack);
    free(stack);
}

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
        push(stack_a, ft_atoi(argv[i]));
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
