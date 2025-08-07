/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:41:52 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/07 22:46:57 by shunwata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_abs(int n)
{
	if (n == -2147483648)
		return (2147483647);
	if (n < 0)
		return (-n);
	return (n);
}

t_node	*node_at(int index, t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (index-- && current)
		current = current->next;
	return (current);
}

int	is_sorted(t_stack *stack)
{
	t_node	*current;

	if (!stack->top || !stack->top->next)
		return (1);
	current = stack->top;
	while (current->next)
	{
		if ((current->value) > (current->next->value))
			return (0);
		current = current->next;
	}
	return (1);
}

int	find_min(t_stack *stack)
{
	int		min_value;
	int		min_index;
	int		i;
	t_node	*current;

	if (stack->size == 0)
		return (0);
	min_value = stack->top->value;
	min_index = 0;
	i = 0;
	current = stack->top;
	while (i < stack->size)
	{
		if (current->value < min_value)
		{
			min_value = current->value;
			min_index = i;
		}
		current = current->next;
		i++;
	}
	return (min_index);
}

int	find_max(t_stack *stack)
{
	int		max_value;
	int		max_index;
	int		i;
	t_node	*current;

	if (stack->size == 0)
		return (0);
	max_value = stack->top->value;
	max_index = 0;
	i = 0;
	current = stack->top;
	while (i < stack->size)
	{
		if (current->value > max_value)
		{
			max_value = current->value;
			max_index = i;
		}
		current = current->next;
		i++;
	}
	return (max_index);
}

int	find_insert_position(t_stack *stack, int to_insert, char stackname)
{
	int		i;
	t_node	*current;
	t_node	*next;

	i = 0;
	current = stack->top;
	while (i < stack->size)
	{
		next = current->next;
		if (!next)
			next = stack->top;
		if (stackname == 'a' \
				&& (current->value < to_insert) && (to_insert < next->value))
			return (i + 1);
		if (stackname == 'b' \
				&& (current->value > to_insert) && (to_insert > next->value))
			return (i + 1);
		current = next;
		i++;
	}
	if (stackname == 'a')
		return (find_min(stack));
	else
		return (find_max(stack));
}

void	get_better_way(t_cost *tmp)
{
	if (tmp->cost_a * tmp->cost_b >= 0)
	{
		if (ft_abs(tmp->cost_a) > ft_abs(tmp->cost_b))
			tmp->total = ft_abs(tmp->cost_a);
		else
			tmp->total = ft_abs(tmp->cost_b);
	}
	else
		tmp->total = ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b);
}

void	get_rough_cost(t_stack *a, t_stack *b, t_cost *tmp)
{
		if (tmp->idx_a <= a->size / 2)
			tmp->cost_a = tmp->idx_a;
		else
			tmp->cost_a = tmp->idx_a - a->size;
		if (tmp->idx_b <= b->size / 2)
			tmp->cost_b = tmp->idx_b;
		else
			tmp->cost_b = tmp->idx_b - b->size;
}

t_cost	best_move_to_a(t_stack *a, t_stack *b)
{
	t_cost	best;
	t_cost	tmp;
	int		i;

	best.total = 2147483647;
	i = 0;
	while (i < b->size)
	{
		tmp.idx_b = i;
		tmp.idx_a = find_insert_position(a, node_at(i, b)->value, 'a');
		get_rough_cost(a, b, &tmp);
		get_better_way(&tmp);
		if (tmp.total < best.total)
			best = tmp;
		i++;
	}
	return (best);
}
t_node	*copy_node(t_node *original)
{
	t_node	*new_node;

	new_node = (t_node *)malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = original->value;
	new_node->lis_flag = original->lis_flag;
	new_node->next = NULL;
	return (new_node);
}

// スタック全体をディープコピーする関数
t_stack	*copy_stack(t_stack *original)
{
	t_stack	*new_stack;
	t_node	*original_curr;
	t_node	*new_curr;
	t_node	*new_head;

	new_stack = (t_stack *)malloc(sizeof(t_stack));
	if (!new_stack)
		return (NULL);
	new_stack->size = original->size;
	if (original->top == NULL)
	{
		new_stack->top = NULL;
		return (new_stack);
	}
	// 最初のノードをコピー
	new_head = copy_node(original->top);
	if (!new_head)
	{
		free(new_stack);
		return (NULL);
	}
	new_stack->top = new_head;
	new_curr = new_head;
	original_curr = original->top->next;
	// 残りのノードをコピーして繋げる
	while (original_curr)
	{
		new_curr->next = copy_node(original_curr);
		if (!new_curr->next)
		{
			free_stack(new_stack); // 失敗したら作成途中のスタックを解放
			return (NULL);
		}
		new_curr = new_curr->next;
		original_curr = original_curr->next;
	}
	return (new_stack);
}

t_cost	best_move_to_a_depth2(t_stack *a, t_stack *b)
{
	t_cost	candidate_move; // 評価対象の「初手」
	t_cost	best_move_so_far; // 最終的に返すべき「最善の初手」
	t_stack	*a_sim;
	t_stack	*b_sim;
	int		min_eval_cost; // 評価用の最小コスト
	int		i;

	min_eval_cost = 2147483647;
	// best_move_so_far を最初の要素で初期化しておく
	best_move_so_far.idx_b = 0;
	best_move_so_far.idx_a = find_insert_position(a, node_at(0, b)->value, 'a');
	get_rough_cost(a, b, &best_move_so_far);
	get_better_way(&best_move_so_far);

	i = 0;
	while (i < b->size)
	{
		// 1. 「初手」の候補とそのコストを計算
		candidate_move.idx_b = i;
		candidate_move.idx_a = find_insert_position(a, node_at(i, b)->value, 'a');
		get_rough_cost(a, b, &candidate_move);
		get_better_way(&candidate_move);

		// 2. スタックをコピーしてシミュレーション
		a_sim = copy_stack(a);
		b_sim = copy_stack(b);
		if (!a_sim || !b_sim)
		{
			free_stack(a_sim);
			free_stack(b_sim);
			error_exit(a, b);
		}

		// 3. コピーしたスタック上で「初手」を実行
		rotate_stacks(a_sim, b_sim, &candidate_move);
		pa(a_sim, b_sim);

		// 4. シミュレート後の状態で、次の手のコストを計算
		int second_move_cost;
		if (b_sim->size > 0)
		{
			// best_move_to_a はコストが最も低い「二手目」を返す
			t_cost next_best_move = best_move_to_a(a_sim, b_sim);
			second_move_cost = next_best_move.total;
		}
		else
		{
			second_move_cost = 0; // Bが空になったらコスト0
		}

		// 5. 評価コストを計算し、最小なら更新
		//    単純な合計ではなく、初手のコストを重視する
		int eval_cost = candidate_move.total + second_move_cost;

		// --- デバッグ用出力 ---
		// printf("i=%d: val=%d, cost1=%d, cost2=%d, eval_cost=%d\n",
		// 	i, node_at(i, b)->value, candidate_move.total, second_move_cost, eval_cost);

		if (eval_cost < min_eval_cost)
		{
			min_eval_cost = eval_cost;
			best_move_so_far = candidate_move;
		}

		// 6. メモリ解放
		free_stack(a_sim);
		free_stack(b_sim);
		i++;
	}

	// printf("==> Chose move for val=%d (b_idx=%d), total_cost=%d\n\n",
	// 	node_at(best_move_so_far.idx_b, b)->value, best_move_so_far.idx_b, best_move_so_far.total);

	return (best_move_so_far);
}

void	sort_three(t_stack *a)
{
	int	first;
	int	second;
	int	third;

	first = a->top->value;
	second = a->top->next->value;
	third = a->top->next->next->value;
	if (first > second && first > third)
		ra(a);
	else if (second > first && second > third)
		rra(a);
	first = a->top->value;
	second = a->top->next->value;
	if (first > second)
		sa(a);
}

void	sort_four(t_stack *a, t_stack *b)
{
	int	min_index;

	min_index = find_min(a);
	if (min_index == 1)
		ra(a);
	else if (min_index == 2)
	{
		ra(a);
		ra(a);
	}
	else if (min_index == 3)
		rra(a);
	if (is_sorted(a))
		return;
	pb(a, b);
	sort_three(a);
	pa(a, b);
}

void	a_piece_of_cake(t_stack *a, t_stack *b)
{
	if (a->size == 2 && (a->top->value) > (a->top->next->value))
		sa(a);
	else if (a->size == 3)
		sort_three(a);
	else if (a->size == 4)
		sort_four(a, b);
}

void	rotate_a(t_stack *a, t_cost *move)
{
	while (move->cost_a > 0)
	{
		ra(a);
		move->cost_a--;
	}
	while (move->cost_a < 0)
	{
		rra(a);
		move->cost_a++;
	}
}

void	rotate_b(t_stack *b, t_cost *move)
{
	while (move->cost_b > 0)
	{
		rb(b);
		move->cost_b--;
	}
	while (move->cost_b < 0)
	{
		rrb(b);
		move->cost_b++;
	}
}

void	rotate_stacks(t_stack *a, t_stack *b, t_cost *move)
{
	while (move->cost_a > 0 && move->cost_b > 0)
	{
		rr(a, b);
		move->cost_a--;
		move->cost_b--;
	}
	while (move->cost_a < 0 && move->cost_b < 0)
	{
		rrr(a, b);
		move->cost_a++;
		move->cost_b++;
	}
	rotate_a(a, move);
	rotate_b(b, move);
}

void	finalize_stack(t_stack *a)
{
	int	min_index;

	min_index = find_min(a);
	if (min_index <= a->size / 2)
	{
		while (min_index--)
			ra(a);
	}
	else
	{
		min_index = a->size - min_index;
		while (min_index--)
			rra(a);
	}
}

int	*stack_to_int_array_2x(t_stack *a)
{
	int		*nums;
	t_node	*current;
	int		size;
	int		i;

	size = a->size;
	nums = malloc(sizeof(int) * size * 2);
	if (!nums)
		return (NULL);
	current = a->top;
	i = 0;
	while (i < size)
	{
		nums[i] = current->value;
		nums[i + size] = current->value;
		current = current->next;
		i++;
	}
	return (nums);
}

void	find_lis(int *nums, int *lis, int *prev, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		lis[i] = 1;
		prev[i] = -1;
		i++;
	}
	i = 1;
	while (i < size)
	{
		j = 0;
		while (j < i)
		{
			if (nums[i] > nums[j] && lis[i] < lis[j] + 1)
			{
				lis[i] = lis[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
}

int	get_max_index(int *lis, int size)
{
	int	max_index;
	int	i;

	max_index = 0;
	i = 1;
	while (i < size)
	{
		if (lis[i] > lis[max_index])
			max_index = i;
		i++;
	}
	return (max_index);
}

void	mark_lis_flag(t_stack *a, int *prev, int max_index, int best_rot)
{
	int		i;
	int		i_in_original;

	i = max_index;
	while (i != -1)
	{
		i_in_original = (i + best_rot) % a->size;
		node_at(i_in_original, a)->lis_flag = 1;
		i = prev[i];
	}
}

int	get_best_rot(int *nums, int *lis, int * prev, int size)
{
	int		current_len;
	int		best_len;
	int		best_rot;
	int		i;

	best_len = 0;
	best_rot = 0;
	i = 0;
	while (i < size)
	{
		find_lis(nums + i, lis, prev, size);
		current_len = lis[get_max_index(lis, size)];
		if (current_len > best_len)
		{
			best_len = current_len;
			best_rot = i;
		}
		i++;
	}
	return (best_rot);
}

int	lis_manage(int *nums, t_stack *a)
{
	int		*lis;
	int		*prev;
	int		best_rot;
	int		max_len;
	int		max_index;

	lis = malloc(sizeof(int) * a->size);
	if (!lis)
		return (-1);
	prev = malloc(sizeof(int) * a->size);
	if (!prev)
		return (free(lis), -1);
	best_rot = get_best_rot(nums, lis, prev, a->size);
	find_lis(nums + best_rot, lis, prev, a->size);
	max_index = get_max_index(lis, a->size);
	max_len = lis[max_index];
	mark_lis_flag(a, prev, max_index, best_rot);
	free(lis);
	free(prev);
	return (max_len);
}

void	turk_sort(t_stack *a, t_stack *b)
{
	t_cost	move;
	int		*nums;
	int		lis;
	int		to_push;
	int		i;

	if (a->size <= 4)
	{
		a_piece_of_cake(a, b);
		return;
	}
	nums = stack_to_int_array_2x(a);
	if (!nums)
		error_exit(a, b);
	lis = lis_manage(nums, a);
	if (lis == -1)
		error_exit(a, b);
	if (lis == a->size)
	{
		finalize_stack(a);
		return;
	}
	to_push = a->size - lis;
	i = 0;
	while (i < to_push)
	{
		if (a->top->lis_flag == 0)
		{
			pb(a,b);
			i++;
		}
		else
			ra(a);
	}
	while (b->size > 0)
	{
		move = best_move_to_a_depth2(a, b);
		rotate_stacks(a, b, &move);
		pa(a, b);
	}
	finalize_stack(a);
}
