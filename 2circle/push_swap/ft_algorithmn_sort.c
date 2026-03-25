/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithmn_sort.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 01:53:15 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 01:27:42 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quick_sort(int *stack_a, int start, int end)
{
	int	pivot;
	int	i;
	int	j;

	pivot = start;
	i = start + 1;
	j = end;
	if (start >= end)
		return ;
	while (i <= j)
	{
		while (i <= end && stack_a[pivot] >= stack_a[i])
			i++;
		while (j > start && stack_a[pivot] <= stack_a[j])
			j--;
		if (i > j)
			ft_swap(&stack_a[j], &stack_a[pivot]);
		else
			ft_swap(&stack_a[i], &stack_a[j]);
	}
	quick_sort(stack_a, start, j - 1);
	quick_sort(stack_a, j + 1, end);
}

void	ft_stack_b_move(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	int	i;
	int	index;
	int	max;

	while (*tail_b > 0)
	{
		i = 1;
		index = 0;
		max = stack_b[0];
		while (i < *tail_b)
		{
			if (max < stack_b[i])
			{
				max = stack_b[i];
				index = i;
			}
			i++;
		}
		if (index < *tail_b / 2)
			ft_exe_rb(index, stack_b, tail_b);
		else
			ft_exe_rrb(index, stack_b, tail_b);
		pa(stack_a, stack_b, tail_a, tail_b);
	}
}
