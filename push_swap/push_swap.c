/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:20:35 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 02:46:01 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	int				*stack_a;
	int				*stack_b;
	int				tail_a;
	int				tail_b;
	t_stack_state	s;

	if (ac < 2)
		exit(1);
	stack_a = ft_parse_input(ac, av, &tail_a);
	if (!stack_a)
		return (0);
	stack_b = ft_calloc(sizeof(int), tail_a);
	tail_b = 0;
	s.stack_a = stack_a;
	s.stack_b = stack_b;
	s.tail_a = &tail_a;
	s.tail_b = &tail_b;
	if (is_sort(stack_a, stack_b, tail_a))
		return (0);
	chunk_sort(&s);
	ft_stack_b_move(stack_a, stack_b, &tail_a, &tail_b);
	free(stack_a);
	free(stack_b);
	return (0);
}
