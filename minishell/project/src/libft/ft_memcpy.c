/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-06 10:49:46 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-06 10:49:46 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cpdest;
	const char	*cpsrc;

	i = 0;
	if (!dest && !src && n > 0)
		return (NULL);
	cpdest = dest;
	cpsrc = src;
	while (i < n)
	{
		*cpdest++ = *cpsrc++;
		i++;
	}
	return (dest);
}
