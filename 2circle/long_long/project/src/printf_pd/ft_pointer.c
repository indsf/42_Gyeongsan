/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:03:36 by inhlee            #+#    #+#             */
/*   Updated: 2025/05/05 21:02:38 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_mk_arr(unsigned long num, int *len)
{
	int				i;
	unsigned long	cpnum;
	char			*arr;

	i = 0;
	cpnum = num;
	while (cpnum != 0)
	{
		cpnum /= 16;
		i++;
	}
	arr = (char *)ft_calloc(sizeof(char), (i + 1));
	*len = i - 1;
	return (arr);
}

static void	ft_fill_hex_ptr(char *str, unsigned long adr, int len, int asc)
{
	while (adr && len-- >= 0)
	{
		if ((adr % 16) < 10)
			str[len + 1] = (adr % 16) + '0';
		else
			str[len + 1] = (adr % 16) + asc;
		adr /= 16;
	}
}

int	ft_pointer(unsigned long adr, int asc)
{
	char	*str;
	int		len;
	int		tmp;

	if (adr == 0)
		return (ft_str("(nil)"));
	str = ft_mk_arr(adr, &len);
	if (!str)
		return (0);
	ft_fill_hex_ptr(str, adr, len, asc);
	tmp = ft_str("0x");
	if (tmp == -1)
	{
		free(str);
		return (-1);
	}
	len = ft_str(str);
	if (len == -1)
	{
		free(str);
		return (-1);
	}
	free(str);
	return (tmp + len);
}
