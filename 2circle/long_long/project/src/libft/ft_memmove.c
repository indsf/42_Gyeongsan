/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-07 07:19:50 by inhlee            #+#    #+#             */
/*   Updated: 2025/04/12 22:41:18 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	char		*dst;
	const char	*ssrc;

	if (!dest && !src)
		return (NULL);
	if (count == 0)
		return (dest);
	if (dest <= src)
	{
		dst = dest;
		ssrc = src;
		while (count--)
			*dst++ = *ssrc++;
	}
	else
	{
		dst = dest;
		dst += count;
		ssrc = src;
		ssrc += count;
		while (count--)
			*--dst = *--ssrc;
	}
	return (dest);
}
