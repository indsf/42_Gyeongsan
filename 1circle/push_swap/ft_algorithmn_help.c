/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_algorithmn_help.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:37:58 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 02:09:32 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_exe_rb(int index, int *stack_b, int *tail_b)
{
	while (index-- > 0)
		rb(stack_b, tail_b);
}

void	ft_exe_rrb(int index, int *stack_b, int *tail_b)
{
	while (index++ < *tail_b)
		rrb(stack_b, tail_b);
}

void	ft_sort_3(int *stack_a, int *tail_a)
{
	int	a;
	int	b;
	int	c;

	a = stack_a[0];
	b = stack_a[1];
	c = stack_a[2];
	if (a > b && b < c && a < c)
		sa(stack_a, tail_a);
	else if (a > b && b > c)
	{
		sa(stack_a, tail_a);
		rra(stack_a, tail_a);
	}
	else if (a > b && b < c && a > c)
		ra(stack_a, tail_a);
	else if (a < b && b > c && a < c)
	{
		sa(stack_a, tail_a);
		ra(stack_a, tail_a);
	}
	else if (a < b && b > c && a > c)
		rra(stack_a, tail_a);
}

void	ft_sort_5(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	int	min;

	while (*tail_a > 3)
	{
		min = find_min(stack_a, *tail_a);
		while (stack_a[0] != min)
			ra(stack_a, tail_a);
		pb(stack_a, stack_b, tail_a, tail_b);
	}
	ft_sort_3(stack_a, tail_a);
	while (*tail_b > 0)
		pa(stack_a, stack_b, tail_a, tail_b);
}

int	ft_chunk_size(t_stack_state *s)
{
	if (*(s->tail_a) == 2)
	{
		ft_sort_2(s->stack_a, s->tail_a);
		return (0);
	}
	if (*(s->tail_a) <= 3)
	{
		ft_sort_3(s->stack_a, s->tail_a);
		return (0);
	}
	else if (*(s->tail_a) <= 5)
	{
		ft_sort_5(s->stack_a, s->stack_b, s->tail_a, s->tail_b);
		return (0);
	}
	else if (*(s->tail_a) == 2 || *(s->tail_a) <= 10)
		return (1);
	else if (*(s->tail_a) <= 50)
		return (2);
	else if (*(s->tail_a) <= 100)
		return (4);
	else
		return (5);
}
