/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_command3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 18:59:59 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 01:57:55 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rrr(int *stack_a, int *stack_b, int *tail_a, int *tail_b)
{
	rra(stack_a, tail_a);
	rrb(stack_b, tail_b);
	write(1, "rrr\n", 4);
}

void	ft_sort_2(int *stack_a, int *tail_a)
{
	if (stack_a[0] > stack_a[1])
		sa(stack_a, tail_a);
	else if (stack_a[0] < stack_a[1])
		sa(stack_a, tail_a);
}
