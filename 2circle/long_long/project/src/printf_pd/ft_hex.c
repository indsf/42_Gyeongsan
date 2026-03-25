/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:02:40 by inhlee            #+#    #+#             */
/*   Updated: 2025/05/05 21:02:27 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_mk_hex(unsigned int hex, int *len)
{
	char	*str;
	int		i;

	i = 0;
	while (hex != 0)
	{
		hex /= 16;
		i++;
	}
	str = (char *)ft_calloc(sizeof(char), i + 1);
	*len = i - 1;
	return (str);
}

static void	ft_ip_hex(char *str, unsigned int hex, int i, int asc)
{
	while (hex != 0 && i-- > 0)
	{
		if ((hex % 16) < 10)
			str[i] = hex % 16 + '0';
		else
			str[i] = hex % 16 + asc;
		hex /= 16;
	}
}

int	ft_hex(unsigned int hex, int asc)
{
	unsigned int	cphex;
	int				len;
	int				result;
	char			*str;

	cphex = hex;
	len = 0;
	if (hex == 0)
		return (ft_char('0'));
	str = ft_mk_hex(hex, &len);
	if (!str)
		return (0);
	ft_ip_hex(str, cphex, len + 1, asc);
	result = ft_str(str);
	if (result == -1)
	{
		free(str);
		return (-1);
	}
	free(str);
	return (result);
}
