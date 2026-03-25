/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 23:14:03 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 22:01:58 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// map의 유효성을 검사 || 가장자리가 1로 되어있는지
static void	check_map(t_game_info *t_game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < t_game->map.width)
	{
		if (t_game->map.map[0][x] != '1' || t_game->map.map[t_game->map.height
			- 1][x] != '1')
			print_err(t_game, "Map_Error_walls\n");
		x++;
	}
	while (y < t_game->map.height)
	{
		if (t_game->map.map[y][0] != '1' || t_game->map.map[y][t_game->map.width
			- 1] != '1')
			print_err(t_game, "Map_Error_walls\n");
		y++;
	}
}

// map에서 개수 확인 필요조건
static int	check_map_count(t_game_info *t_game)
{
	int	i;
	int	j;

	i = -1;
	t_game->map.player = 0;
	t_game->map.coin = 0;
	t_game->map.door = 0;
	while (t_game->map.map[++i])
	{
		j = -1;
		while (t_game->map.map[i][++j])
		{
			if (t_game->map.map[i][j] == 'C')
				t_game->map.coin++;
			else if (t_game->map.map[i][j] == 'P')
				t_game->map.player++;
			else if (t_game->map.map[i][j] == 'E')
				t_game->map.door++;
			else if (t_game->map.map[i][j] != '0'
					&& t_game->map.map[i][j] != '1')
				return (1);
		}
	}
	return (t_game->map.coin < 1 || t_game->map.player != 1
		|| t_game->map.door != 1);
}

void	map_check(t_game_info *t_game)
{
	check_map(t_game);
	if (check_map_count(t_game))
		print_err(t_game, "Map params error.\n");
}
