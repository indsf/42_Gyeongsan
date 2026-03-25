/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:12:47 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 21:43:48 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(t_game_info *t_game)
{
	int	i;

	i = 0;
	if (t_game->map.map)
	{
		while (t_game->map.map[i])
		{
			free(t_game->map.map[i]);
			i++;
		}
		free(t_game->map.map);
		t_game->map.map = NULL;
	}
	if (t_game->map.line)
	{
		free(t_game->map.line);
		t_game->map.line = NULL;
	}
	if (t_game->map.path)
	{
		free(t_game->map.path);
		t_game->map.path = NULL;
	}
}

// '\n'전까지 길이 자르기
size_t	trimmed_len(const char *s)
{
	size_t	n;

	n = (int)ft_strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
		n--;
	return (n);
}
