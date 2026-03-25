/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_util2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 20:42:21 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 01:28:19 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_split_size(char *str)
{
	int	i;
	int	size;
	int	flag;

	i = 0;
	size = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] && !ft_isspace(str[i]) && flag == 0)
		{
			size++;
			flag = 1;
		}
		else if (str[i] && ft_isspace(str[i]) && flag == 1)
			flag = 0;
		i++;
	}
	if (size == 0)
		return (ft_print_error(1));
	return (size);
}

int	ft_count_total_words(int ac, char **str)
{
	int	i;
	int	total;

	i = 1;
	total = 0;
	while (i < ac)
	{
		total += ft_split_size(str[i]);
		i++;
	}
	return (total);
}

int	find_min(int *stack, int size)
{
	int	i;
	int	min;

	i = 1;
	min = stack[0];
	while (i < size)
	{
		if (stack[i] < min)
			min = stack[i];
		i++;
	}
	return (min);
}
