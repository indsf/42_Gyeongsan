/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:03:07 by inhlee            #+#    #+#             */
/*   Updated: 2025/05/02 06:25:54 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len(int num)
{
	int	i;

	i = 0;
	if (num <= 0)
		i++;
	while (num != 0)
	{
		num /= 10;
		i++;
	}
	return (i);
}

static int	ft_putnbr(int n)
{
	char	c;
	int		temp;
	long	cpn;

	cpn = n;
	if (cpn != -2147483648 && cpn < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		cpn = -cpn;
	}
	if (cpn >= 10)
	{
		temp = ft_putnbr(cpn / 10);
		if (temp == -1)
			return (-1);
	}
	c = (cpn % 10) + '0';
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}

int	ft_int(int num)
{
	int	len;

	len = ft_len(num);
	if (num == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	if (ft_putnbr(num) == -1)
		return (-1);
	return (len);
}
