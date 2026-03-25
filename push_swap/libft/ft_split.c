/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:39:14 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/09 22:55:30 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordcnt(char const *s, char c)
{
	size_t	cnt;
	size_t	flag;

	cnt = 0;
	if (!s || *s == '\0')
		return (0);
	flag = 0;
	while (*s)
	{
		if (*s != c && !flag)
		{
			cnt++;
			flag = 1;
		}
		else if (*s == c)
			flag = 0;
		s++;
	}
	return (cnt);
}

static void	*ft_free(char **s)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
	return (NULL);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	if (n == 0)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (n + 1));
	if (!str)
		return (NULL);
	while (i < n && s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	wdlen;
	char	**arr;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (ft_wordcnt(s, c) + 1));
	if (!arr)
		return (NULL);
	while (i < ft_wordcnt(s, c) && s[j] != '\0')
	{
		while (s[j] == c)
			j++;
		wdlen = j;
		while (s[j] != c && s[j] != '\0')
			j++;
		arr[i] = ft_strndup(&s[wdlen], j - wdlen);
		if (!arr[i++])
			return (ft_free(arr));
	}
	arr[ft_wordcnt(s, c)] = NULL;
	return (arr);
}
