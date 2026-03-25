/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_record.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:55:13 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 15:19:10 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	find_exit(t_game_info *t_game)
{
	int	x;
	int	y;
	int	find;

	find = 0;
	y = 0;
	while (y < t_game->map.height && !find)
	{
		x = 0;
		while (x < t_game->map.width)
		{
			if (t_game->map.map[y][x] == 'E')
			{
				t_game->door_x = x;
				t_game->door_y = y;
				find = 1;
				break ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_game_info *t_game)
{
	int	x;
	int	y;

	y = 0;
	while (y < t_game->map.height)
	{
		x = 0;
		while (x < t_game->map.width)
		{
			if (t_game->map.map[y][x] == 'P')
			{
				t_game->player_x = x;
				t_game->player_y = y;
			}
			x++;
		}
		y++;
	}
	find_exit(t_game);
}
