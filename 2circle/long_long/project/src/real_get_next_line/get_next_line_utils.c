/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 23:40:46 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/21 17:59:37 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*gnl_strchr(const char *s, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if (s[i] == fd)
			return ((char *)s + i);
		i++;
	}
	if (fd == '\0')
		return ((char *)s + i);
	else
		return (NULL);
}

void	*gnl_calloc(size_t num, size_t size)
{
	unsigned char	*str;
	size_t			i;

	i = 0;
	if (num != 0 && size > __SIZE_MAX__ / num)
		return (NULL);
	str = (unsigned char *)malloc(num * size);
	if (!str)
		return (NULL);
	while (i < num * size)
	{
		str[i] = 0;
		i++;
	}
	return ((void *)str);
}

char	*gnl_strdup(const char *s)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	len = gnl_strlen(s);
	str = (char *)gnl_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	while (*s)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_strjoin(char *backup, char *buff)
{
	int		i;
	char	*str;
	int		len;

	i = 0;
	len = gnl_strlen(backup) + gnl_strlen(buff);
	str = (char *)gnl_calloc(len + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (backup && *backup)
	{
		str[i] = *backup;
		i++;
		backup++;
	}
	while (buff && *buff)
	{
		str[i] = *buff;
		i++;
		buff++;
	}
	str[i] = '\0';
	return (str);
}
