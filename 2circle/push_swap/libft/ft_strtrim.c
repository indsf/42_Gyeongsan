/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-06 11:01:56 by inhlee            #+#    #+#             */
/*   Updated: 2025-04-06 11:01:56 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	last;
	char	*arr;

	start = 0;
	last = ft_strlen(s1);
	if (!s1 || !set)
		return (NULL);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (last > start && ft_strchr(set, s1[last - 1]))
		last--;
	if (start >= last)
	{
		arr = malloc(1);
		if (!arr)
			return (NULL);
		arr[0] = '\0';
		return (arr);
	}
	arr = (char *)malloc(sizeof(char) * (last - start + 1));
	if (!arr)
		return (NULL);
	ft_strlcpy(arr, s1 + start, last - start + 1);
	return (arr);
}
