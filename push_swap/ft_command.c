/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 19:40:51 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 02:07:12 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sa(int *stack_a, int *tail_a)
{
	int	tmp;

	if (*tail_a < 2)
		return ;
	tmp = *stack_a;
	*stack_a = *(stack_a + 1);
	*(stack_a + 1) = tmp;
	write(1, "sa\n", 3);
}

void	sb(int *stack_b, int *tail_b)
{
	int	tmp;

	if (*tail_b < 2)
		return ;
	tmp = *stack_b;
	*stack_b = *(stack_b + 1);
	*(stack_b + 1) = tmp;
	write(1, "sb\n", 3);
}

void	ss(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	sa(stack_a, tail_a);
	sb(stack_b, tail_b);
	write(1, "ss\n", 3);
}

void	pa(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	int	i;

	if (*tail_b == 0)
		return ;
	i = *tail_a;
	while (i > 0)
	{
		stack_a[i] = stack_a[i - 1];
		i--;
	}
	stack_a[0] = stack_b[0];
	(*tail_a)++;
	i = 0;
	while (i < *tail_b - 1)
	{
		stack_b[i] = stack_b[i + 1];
		i++;
	}
	(*tail_b)--;
	write(1, "pa\n", 3);
}

void	pb(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	int	i;

	if (*tail_a == 0)
		return ;
	i = *tail_b;
	while (i > 0)
	{
		stack_b[i] = stack_b[i - 1];
		i--;
	}
	stack_b[0] = stack_a[0];
	(*tail_b)++;
	i = 0;
	while (i < *tail_a - 1)
	{
		stack_a[i] = stack_a[i + 1];
		i++;
	}
	(*tail_a)--;
	write(1, "pb\n", 3);
}
