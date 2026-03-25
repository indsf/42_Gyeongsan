/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 14:38:58 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/04 02:44:51 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_free_append(char *backup, char *buffer)
{
	char	*temp;

	temp = gnl_strjoin(backup, buffer);
	free(backup);
	return (temp);
}

static char	*ft_read_line(int fd, char *backup)
{
	char	*buffer;
	int		count;

	count = 1;
	buffer = gnl_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	while (count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count == -1 || (count == 0 && (!backup || *backup == '\0')))
		{
			free(backup);
			free(buffer);
			return (NULL);
		}
		else if (count == 0)
			break ;
		buffer[count] = '\0';
		backup = ft_free_append(backup, buffer);
		if (gnl_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (backup);
}

static char	*ft_extract(char *buffer)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!buffer || *buffer == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = gnl_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	return (line);
}

static char	*ft_next_line(char *buffer)
{
	int		i;
	int		j;
	char	*backup;

	i = 0;
	j = 0;
	if (!buffer || *buffer == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	backup = gnl_calloc(gnl_strlen(buffer) - i + 1, sizeof(char));
	i++;
	if (!backup)
		return (NULL);
	while (buffer[i])
		backup[j++] = buffer[i++];
	free(buffer);
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (fd < 0)
	{
		free(buffer);
		buffer = NULL;
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = gnl_calloc(1, 1);
	if (!gnl_strchr(buffer, '\n'))
		buffer = ft_read_line(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_extract(buffer);
	buffer = ft_next_line(buffer);
	return (line);
}
