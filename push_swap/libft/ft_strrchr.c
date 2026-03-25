/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-06 10:52:12 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-06 10:52:12 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len > 0)
	{
		if (s[len - 1] == (unsigned char)c)
		{
			return ((char *)(s + len - 1));
		}
		len--;
	}
	if ((unsigned char)c == '\0')
		return ((char *)(s + ft_strlen(s)));
	return (NULL);
}
