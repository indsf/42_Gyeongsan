/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:03:27 by inhlee            #+#    #+#             */
/*   Updated: 2025/05/02 06:41:50 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_un_print(unsigned int n)
{
	char	c;
	int		len;

	if (n >= 10)
	{
		len = ft_un_print(n / 10);
		if (len == -1)
			return (-1);
	}
	else
		len = 0;
	c = n % 10 + '0';
	if (ft_char(c) == -1)
		return (-1);
	return (len + 1);
}

int	ft_unsigned(unsigned int num)
{
	if (num == 0)
		return (ft_char('0'));
	return (ft_un_print(num));
}
