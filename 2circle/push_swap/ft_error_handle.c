/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 23:47:23 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/20 03:50:11 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_atoi_check(const char *str)
{
	int			check;
	int			sign;
	long long	result;

	check = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = (result * 10) + (*str - '0');
		ft_min_max_check(sign, result);
		str++;
	}
	if (*str != '\0')
		ft_print_error(1);
	return ((int)sign * result);
}

char	**ft_split_all(int ac, char **str)
{
	char	**arr;
	char	**tmp;
	int		i;
	int		j;
	int		k;

	i = 1;
	k = 0;
	arr = (char **)malloc(sizeof(char *) * (ft_count_total_words(ac, str) + 1));
	if (!arr)
		return (NULL);
	while (i < ac)
	{
		tmp = ft_split(str[i++], ' ');
		if (!tmp)
			return (NULL);
		j = 0;
		while (tmp[j])
			arr[k++] = ft_strdup(tmp[j++]);
		ft_free_split(tmp);
	}
	arr[k] = NULL;
	return (arr);
}

int	ft_double_check(int *arr, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (arr[i] == arr[j])
			{
				return 1;
			}
			j++;
		}
		i++;
	}
	return 0;
}

int	*ft_parse_input(int ac, char **av, int *size)
{
	char	**split;
	int		count;
	int		*arr;
	int		i;

	split = ft_split_all(ac, av);
	i = 0;
	count = 0;
	while (split[count])
		count++;
	arr = (int *)malloc(sizeof(int) * count);
	if (!arr)
		return (0);
	while (i < count)
	{
		arr[i] = ft_atoi_check(split[i]);
		i++;
	}
	
	if(ft_double_check(arr, count)  == 1)
	{
		ft_free_split(split);
		free(arr);
		ft_print_error(1);
	}
	ft_free_split(split);
	*size = count;
	return (arr);
}

int	is_sort(int *stack_a, int *stack_b, int tail_a)
{
	int	i;

	i = 0;
	while (i < tail_a - 1)
	{
		if (stack_a[i] > stack_a[i + 1])
			return (0);
		i++;
	}
	free(stack_a);
	free(stack_b);
	return (1);
}
