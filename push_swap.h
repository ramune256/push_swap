/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:54:10 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/03 17:15:00 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	push_swap_h
# define push_swap_h

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct	s_stack
{
	t_node	*top;
	int		size;
}	t_stack;

typedef struct	s_cost
{
	int		idx_a;
	int		idx_b;
	int		cost_a;
	int		cost_b;
	int		total;
}	t_cost;

#endif
