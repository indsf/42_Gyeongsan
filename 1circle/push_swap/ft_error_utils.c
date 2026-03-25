/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:33:57 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 01:40:11 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_isspace(char str)
{
	return ((str >= 9 && str <= 13) || str == 32);
}

int	ft_print_error(int num)
{
	if (num >= 1)
		write(2, "Error\n", 6);
	exit(1);
	return (-1);
}

void	ft_free_split(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
		free(split_arr[i++]);
	free(split_arr);
}

int	ft_empty_check(char **arr)
{
	if (!arr)
		return (0);
	else
		return (1);
}

void	ft_min_max_check(int sign, long long result)
{
	if ((sign == 1 && result > 2147483647) || (sign == -1
			&& result > 2147483648))
		ft_print_error(1);
}
