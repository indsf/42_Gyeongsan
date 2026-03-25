/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-06 10:53:03 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-06 10:53:03 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t len)
{
	unsigned char	*ss;
	unsigned char	cc;
	size_t			i;

	ss = (unsigned char *)s;
	cc = (unsigned char)c;
	i = 0;
	while (i < len)
	{
		if (ss[i] == cc)
		{
			return ((char *)(ss + i));
		}
		i++;
	}
	return (NULL);
}
