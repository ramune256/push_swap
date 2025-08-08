/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shunwata <shunwata@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 16:41:52 by shunwata          #+#    #+#             */
/*   Updated: 2025/08/09 01:30:43 by shunwata         ###   ########.fr       */
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
	int	count;

	min_index = find_min(a);
	if (min_index <= a->size / 2)
	{
		while (min_index--)
			ra(a);
	}
	else
	{
		count = a->size - min_index;
		while (count--)
			rra(a);
	}
	if (is_sorted(a))
		return;
	pb(a, b);
	sort_three(a);
	pa(a, b);
}

void	sort_five(t_stack *a, t_stack *b)
{
	int	min_index;
	int	count;

	min_index = find_min(a);
	if (min_index <= a->size / 2)
	{
		while (min_index--)
			ra(a);
	}
	else
	{
		count = a->size - min_index;
		while (count--)
			rra(a);
	}
	if (is_sorted(a))
		return;
	pb(a, b);
	sort_four(a, b);
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
	else if (a->size == 5)
		sort_five(a, b);
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

int	*stack_to_int_array_2x(t_stack *a, t_stack *b)
{
	int		*nums;
	t_node	*current;
	int		size;
	int		i;

	size = a->size;
	nums = malloc(sizeof(int) * size * 2);
	if (!nums)
		error_exit(a, b);
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
		return(-1);
	prev = malloc(sizeof(int) * a->size);
	if (!prev)
		return(free(lis), -1);
	best_rot = get_best_rot(nums, lis, prev, a->size);
	find_lis(nums + best_rot, lis, prev, a->size);
	max_index = get_max_index(lis, a->size);
	max_len = lis[max_index];
	mark_lis_flag(a, prev, max_index, best_rot);
	free(lis);
	free(prev);
	return (max_len);
}

int	search_lis(t_stack *a, t_stack *b)
{
	int	*nums;
	int	lis;

	nums = stack_to_int_array_2x(a, b);
	lis = lis_manage(nums, a);
	free(nums);
	if (lis == -1)
		error_exit(a, b);
	return (lis);
}

void	swap_int(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int	partition(int *arr, int low, int high)
{
	int	pivot_value;
	int	i;
	int	j;

	pivot_value = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] < pivot_value)
		{
			i++;
			swap_int(&arr[i], &arr[j]);
		}
		j++;
	}
	swap_int(&arr[i + 1], &arr[high]);
	return (i + 1);
}

int	quickselect(int *arr, int low, int high, int k)
{
	int	pivot_index;

	if (low <= high)
	{
		pivot_index = partition(arr, low, high);
		if (pivot_index == k)
			return (arr[pivot_index]);
		else if (pivot_index > k)
			return (quickselect(arr, low, pivot_index - 1, k));
		else
			return (quickselect(arr, pivot_index + 1, high, k));
	}
	return (-1);
}

int	find_pivot(t_stack *a)
{
	t_node	*current;
	int		*arr;
	int		size;
	int		pivot;
	int		i;

	size = a->size;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (-1);
	current = a->top;
	i = 0;
	while (i < size)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	pivot = quickselect(arr, 0, size - 1, size / 2);
	free(arr);
	return (pivot);
}

// 改善されたピボット選択関数
int	find_optimized_pivot(t_stack *a)
{
	t_node	*current;
	int		*arr;
	int		size;
	int		pivot;
	int		i;

	size = a->size;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (-1);
	current = a->top;
	i = 0;
	while (i < size)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}
	// より効率的なピボット選択（25%と75%の位置）
	int	lower_pivot = quickselect(arr, 0, size - 1, size / 4);
	int	upper_pivot = quickselect(arr, 0, size - 1, 3 * size / 4);
	pivot = (lower_pivot + upper_pivot) / 2;
	free(arr);
	return (pivot);
}

// 改善されたpush_non_lis_to_b関数
void	push_non_lis_to_b_optimized(t_stack *a, t_stack *b, int lis)
{
	int		pivot;
	int		to_push;
	int		smaller_count;
	int		larger_count;

	pivot = find_optimized_pivot(a);
	if (pivot == -1)
		error_exit(a, b);
	to_push = a->size - lis;
	smaller_count = 0;
	larger_count = 0;

	while (to_push > 0)
	{
		if (a->top->lis_flag == 0)
		{
			pb(a, b);
			to_push--;
			// より効率的なスタックBの管理
			if (b->size > 1)
			{
				if (b->top->value <= pivot)
				{
					rb(b);
					smaller_count++;
				}
				else
					larger_count++;
			}
		}
		else
			ra(a);
	}
}

// 改善されたpush_back_to_a関数
void	push_back_to_a_optimized(t_stack *a, t_stack *b)
{
	t_cost	move;
	int		best_value;
	int		i;

	while (b->size > 0)
	{
		// より効率的な最適移動の計算
		move = best_move_to_a(a, b);

		// 同時回転の最適化
		rotate_stacks(a, b, &move);
		pa(a, b);
	}
}

// 新しい最適化されたソート関数
void	my_sort_optimized(t_stack *a, t_stack *b)
{
	int		lis;

	if (a->size <= 5)
	{
		a_piece_of_cake(a, b);
		return;
	}

	lis = search_lis(a, b);
	if (lis == a->size)
	{
		finalize_stack(a);
		return;
	}

	// 改善された関数を使用
	push_non_lis_to_b_optimized(a, b, lis);
	push_back_to_a_optimized(a, b);
	finalize_stack(a);
}

// チャンクソート用の関数
void	chunk_sort(t_stack *a, t_stack *b)
{
	int		chunk_size;
	int		chunk_start;
	int		chunk_end;
	int		pivot;
	int		i;
	int		pushed;

	chunk_size = a->size / 4; // より小さなチャンクサイズ
	if (chunk_size < 1)
		chunk_size = 1;

	chunk_start = 0;
	while (a->size > 5)
	{
		chunk_end = chunk_start + chunk_size;
		if (chunk_end > a->size)
			chunk_end = a->size;

		// チャンク内のピボットを見つける
		pivot = find_chunk_pivot(a, chunk_start, chunk_end);

		pushed = 0;
		i = 0;
		while (i < a->size && pushed < chunk_size)
		{
			if (a->top->value <= pivot)
			{
				pb(a, b);
				pushed++;
				// スタックBを効率的に管理
				if (b->size > 1 && b->top->value < pivot)
					rb(b);
			}
			else
				ra(a);
		}

		chunk_start += chunk_size;
	}

	// 残りの要素をソート
	a_piece_of_cake(a, b);

	// スタックBからAに戻す
	push_back_to_a_optimized(a, b);
}

// チャンク内のピボットを見つける関数
int	find_chunk_pivot(t_stack *a, int start, int end)
{
	t_node	*current;
	int		*arr;
	int		size;
	int		pivot;
	int		i;

	size = end - start;
	arr = malloc(sizeof(int) * size);
	if (!arr)
		return (-1);

	current = node_at(start, a);
	i = 0;
	while (i < size)
	{
		arr[i] = current->value;
		current = current->next;
		i++;
	}

	pivot = quickselect(arr, 0, size - 1, size / 2);
	free(arr);
	return (pivot);
}

// より効率的なLISアルゴリズム
int	search_lis_optimized(t_stack *a, t_stack *b)
{
	int	*nums;
	int	lis;

	nums = stack_to_int_array_2x(a, b);
	lis = lis_manage_optimized(nums, a);
	free(nums);
	if (lis == -1)
		error_exit(a, b);
	return (lis);
}

// 最適化されたLIS管理関数
int	lis_manage_optimized(int *nums, t_stack *a)
{
	int		*lis;
	int		*prev;
	int		best_rot;
	int		max_len;
	int		max_index;

	lis = malloc(sizeof(int) * a->size);
	if (!lis)
		return(-1);
	prev = malloc(sizeof(int) * a->size);
	if (!prev)
		return(free(lis), -1);

	// より効率的な回転検索
	best_rot = get_best_rot_optimized(nums, lis, prev, a->size);
	find_lis(nums + best_rot, lis, prev, a->size);
	max_index = get_max_index(lis, a->size);
	max_len = lis[max_index];
	mark_lis_flag(a, prev, max_index, best_rot);

	free(lis);
	free(prev);
	return (max_len);
}

// 最適化された回転検索
int	get_best_rot_optimized(int *nums, int *lis, int *prev, int size)
{
	int		current_len;
	int		best_len;
	int		best_rot;
	int		i;
	int		step;

	best_len = 0;
	best_rot = 0;
	step = size / 8; // より粗い検索
	if (step < 1)
		step = 1;

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
		i += step;
	}

	// 最適な回転の周辺を細かく検索
	int	start = best_rot - step;
	int	end = best_rot + step;
	if (start < 0)
		start = 0;
	if (end > size)
		end = size;

	i = start;
	while (i < end)
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

// 最終的な最適化されたソート関数
void	my_sort_final(t_stack *a, t_stack *b)
{
	if (a->size <= 5)
	{
		a_piece_of_cake(a, b);
		return;
	}

	// サイズに応じてアルゴリズムを選択
	if (a->size <= 100)
	{
		// 小さなサイズではチャンクソートを使用
		chunk_sort(a, b);
	}
	else
	{
		// 大きなサイズでは最適化されたLISを使用
		int	lis = search_lis_optimized(a, b);
		if (lis == a->size)
		{
			finalize_stack(a);
			return;
		}
		push_non_lis_to_b_optimized(a, b, lis);
		push_back_to_a_optimized(a, b);
		finalize_stack(a);
	}
}

// 超最適化されたソート関数（500要素用）
void	my_sort_ultra_optimized(t_stack *a, t_stack *b)
{
	if (a->size <= 5)
	{
		a_piece_of_cake(a, b);
		return;
	}

	// 500要素用の特別な最適化
	if (a->size == 500)
	{
		// より効率的なチャンクサイズ
		chunk_sort_optimized(a, b, 15); // より小さなチャンク
	}
	else if (a->size <= 100)
	{
		chunk_sort(a, b);
	}
	else
	{
		int	lis = search_lis_optimized(a, b);
		if (lis == a->size)
		{
			finalize_stack(a);
			return;
		}
		push_non_lis_to_b_optimized(a, b, lis);
		push_back_to_a_optimized(a, b);
		finalize_stack(a);
	}
}

// 最適化されたチャンクソート
void	chunk_sort_optimized(t_stack *a, t_stack *b, int chunk_size)
{
	int		chunk_start;
	int		chunk_end;
	int		pivot;
	int		i;
	int		pushed;
	int		rotations;

	chunk_start = 0;
	while (a->size > 5)
	{
		chunk_end = chunk_start + chunk_size;
		if (chunk_end > a->size)
			chunk_end = a->size;

		pivot = find_chunk_pivot(a, chunk_start, chunk_end);

		pushed = 0;
		rotations = 0;
		i = 0;
		while (i < a->size && pushed < chunk_size)
		{
			if (a->top->value <= pivot)
			{
				pb(a, b);
				pushed++;
				// より効率的なスタックB管理
				if (b->size > 1)
				{
					if (b->top->value < pivot / 2)
						rb(b);
				}
			}
			else
			{
				ra(a);
				rotations++;
			}
			i++;
		}

		// 回転を最適化
		if (rotations > a->size / 2)
		{
			rotations = a->size - rotations;
			while (rotations--)
				rra(a);
		}

		chunk_start += chunk_size;
	}

	a_piece_of_cake(a, b);
	push_back_to_a_optimized(a, b);
}

// より効率的なpush_back_to_a関数
void	push_back_to_a_ultra_optimized(t_stack *a, t_stack *b)
{
	t_cost	move;
	int		best_value;
	int		i;
	int		consecutive_moves;

	while (b->size > 0)
	{
		// 連続した最適移動を計算
		consecutive_moves = 0;
		while (b->size > 0 && consecutive_moves < 3)
		{
			move = best_move_to_a(a, b);

			// 同時回転の最適化
			rotate_stacks(a, b, &move);
			pa(a, b);
			consecutive_moves++;
		}
	}
}

void	push_non_lis_to_b(t_stack *a, t_stack *b, int lis)
{
	int	pivot;
	int	to_push;

	pivot = find_pivot(a);
	if (pivot == -1)
		error_exit(a, b);
	to_push = a->size - lis;
	while (to_push > 0)
	{
		if (a->top->lis_flag == 0)
		{
			pb(a, b);
			to_push--;
			if (b->top->value <= pivot && b->size > 1)
				rb(b);
		}
		else
			ra(a);
	}
}

void	push_back_to_a(t_stack *a, t_stack *b)
{
	t_cost	move;

	while (b->size > 0)
	{
		move = best_move_to_a(a, b);
		rotate_stacks(a, b, &move);
		pa(a, b);
	}
}

void	my_sort(t_stack *a, t_stack *b)
{
	int		lis;

	if (a->size <= 5)
	{
		a_piece_of_cake(a, b);
		return;
	}
	lis = search_lis(a, b);
	if (lis == a->size)
	{
		finalize_stack(a);
		return;
	}
	push_non_lis_to_b(a, b, lis);
	push_back_to_a(a, b);
	finalize_stack(a);
}
