/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-05 10:56:17 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-05 10:56:17 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(long n)
{
	int	len;

	len = 0;
	if (n == 0)
	{
		return (1);
	}
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static char	*make_arr(char *arr, int n)
{
	long	nb;
	int		len;

	nb = n;
	len = ft_len(n);
	if (nb < 0)
	{
		arr[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		arr[--len] = nb % 10 + 48;
		nb = (nb / 10);
	}
	return (arr);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*arr;

	len = ft_len(n);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	arr[len] = '\0';
	if (n == 0)
	{
		arr[0] = '0';
		return (arr);
	}
	return (make_arr(arr, n));
}
