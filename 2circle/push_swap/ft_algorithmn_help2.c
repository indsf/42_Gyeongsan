/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithmn_help2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 20:27:06 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 02:08:46 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*ft_sorted(int *stack_a, int *tail_a)
{
	int	*sort;
	int	i;

	sort = malloc(sizeof(int) * (*tail_a));
	i = 0;
	if (!sort)
		return (NULL);
	while (i < *tail_a)
	{
		sort[i] = stack_a[i];
		i++;
	}
	quick_sort(sort, 0, *tail_a - 1);
	return (sort);
}

t_chunk_info	ft_get_value(int *sort, int size, int start, int chunk_size)
{
	t_chunk_info	info;
	int				min_idx;
	int				max_idx;

	min_idx = start * chunk_size;
	max_idx = (start + 1) * chunk_size - 1;
	if (min_idx >= size)
	{
		info.min = -1;
		return (info);
	}
	if (max_idx >= size)
		max_idx = size - 1;
	info.min = sort[min_idx];
	info.max = sort[max_idx];
	info.mid = (info.min + info.max) / 2;
	return (info);
}

int	ft_value_in_range(int *stack_a, int size, int min, int max)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (stack_a[i] >= min && stack_a[i] <= max)
			return (1);
		i++;
	}
	return (0);
}

void	ft_excute(t_stack_state *stack_info, t_chunk_info info)
{
	while (ft_value_in_range(stack_info->stack_a, *(stack_info->tail_a),
			info.min, info.max))
	{
		if (stack_info->stack_a[0] >= info.min
			&& stack_info->stack_a[0] <= info.max)
		{
			pb(stack_info->stack_a, stack_info->stack_b, stack_info->tail_a,
				stack_info->tail_b);
			if (stack_info->stack_b[0] < info.mid)
				rb(stack_info->stack_b, stack_info->tail_b);
		}
		else
			ra(stack_info->stack_a, stack_info->tail_a);
	}
}

void	chunk_sort(t_stack_state *s)
{
	t_chunk_info	info;
	t_chunk_size	chunk;
	int				start;
	int				*sort;

	chunk.size = *(s->tail_a);
	chunk.chunk = ft_chunk_size(s);
	if (chunk.chunk == 0)
		return ;
	chunk.chunk_size = chunk.size / chunk.chunk;
	start = 0;
	sort = ft_sorted(s->stack_a, s->tail_a);
	if (!sort)
		return ;
	if (chunk.size % chunk.chunk != 0)
		chunk.chunk_size += (chunk.size % chunk.chunk);
	while (start < chunk.chunk)
	{
		info = ft_get_value(sort, chunk.size, start, chunk.chunk_size);
		if (info.min == -1)
			break ;
		ft_excute(s, info);
		start++;
	}
	free(sort);
}
