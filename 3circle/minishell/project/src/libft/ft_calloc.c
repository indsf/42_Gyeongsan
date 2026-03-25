/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-06 10:58:30 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-06 10:58:30 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*arr;
	size_t			i;

	if (num != 0 && size > __SIZE_MAX__ / num)
		return (NULL);
	arr = (unsigned char *)malloc(num * size);
	i = 0;
	if (!arr)
		return (NULL);
	while (i < num * size)
	{
		arr[i] = 0;
		i++;
	}
	return ((void *)arr);
}
