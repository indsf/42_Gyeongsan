/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 19:16:47 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/18 22:07:49 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rra(int *stack_a, int *tail_a)
{
	int	i;
	int	top;

	if (*tail_a < 2)
		return ;
	i = 0;
	top = stack_a[(*tail_a) - 1];
	while (i < (*tail_a) - 1)
	{
		stack_a[(*tail_a) - 1 - i] = stack_a[(*tail_a) - 2 - i];
		i++;
	}
	stack_a[0] = top;
	write(1, "rra\n", 4);
}

void	rrb(int *stack_b, int *tail_b)
{
	int	i;
	int	top;

	if (*tail_b < 2)
		return ;
	i = 0;
	top = stack_b[(*tail_b) - 1];
	while (i < (*tail_b) - 1)
	{
		stack_b[(*tail_b) - 1 - i] = stack_b[(*tail_b) - 2 - i];
		i++;
	}
	stack_b[0] = top;
	write(1, "rrb\n", 4);
}

void	rr(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	ra(stack_a, tail_a);
	rb(stack_b, tail_b);
	write(1, "rr\n", 3);
}

void	ra(int *stack_a, int *tail_a)
{
	int	i;
	int	head;

	if (*tail_a < 2)
		return ;
	i = 0;
	head = stack_a[0];
	while (i < (*tail_a) - 1)
	{
		stack_a[i] = stack_a[i + 1];
		i++;
	}
	stack_a[i] = head;
	write(1, "ra\n", 3);
}

void	rb(int *stack_b, int *tail_b)
{
	int	i;
	int	head;

	if (*tail_b < 2)
		return ;
	i = 0;
	head = stack_b[0];
	while (i < (*tail_b) - 1)
	{
		stack_b[i] = stack_b[i + 1];
		i++;
	}
	stack_b[i] = head;
	write(1, "rb\n", 3);
}
