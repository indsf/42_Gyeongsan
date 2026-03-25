/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 00:32:31 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 21:59:11 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_visit(int **visited, int height)
{
	int	i;

	i = 0;
	while (i < height)
		free(visited[i++]);
	free(visited);
}

static int	**create_visit(t_game_info *t_game)
{
	int	i;
	int	j;
	int	**visit;

	i = -1;
	visit = (int **)malloc(sizeof(int *) * t_game->map.height);
	if (!visit)
		return (0);
	while (++i < t_game->map.height)
	{
		visit[i] = (int *)malloc(sizeof(int) * (t_game->map.width + 1));
		if (!visit[i])
		{
			free_visit(visit, i);
			return (NULL);
		}
		j = -1;
		while (j < t_game->map.width)
			visit[i][++j] = 0;
	}
	return (visit);
}

static void	ft_dfs(t_game_info *t_game, t_check *check, int y, int x)
{
	const int	dy[4] = {1, -1, 0, 0};
	const int	dx[4] = {0, 0, 1, -1};
	int			i;
	int			nx;
	int			ny;

	check->visited[y][x] = 1;
	if (t_game->map.map[y][x] == 'C')
		check->collectible -= 1;
	if (t_game->map.map[y][x] == 'E')
		t_game->map.valid_path = 1;
	i = -1;
	while (++i < 4)
	{
		ny = y + dy[i];
		nx = x + dx[i];
		if (t_game->map.map[ny][nx] != '1' && !check->visited[ny][nx])
			ft_dfs(t_game, check, ny, nx);
	}
}

static void	init_check(t_game_info *t_game, t_check *check)
{
	ft_memset(check, 0, sizeof(t_check));
	check->visited = create_visit(t_game);
	check->y = t_game->map.height;
	check->x = t_game->map.width;
	t_game->map.valid_path = 0;
	check->collectible = t_game->map.coin;
}

void	check_path(t_game_info *t_game)
{
	t_check	check;

	init_check(t_game, &check);
	ft_dfs(t_game, &check, t_game->player_y, t_game->player_x);
	if (!t_game->map.valid_path || check.collectible > 0)
	{
		free_visit(check.visited, t_game->map.height);
		print_err(t_game, "not_find_path");
	}
	free_visit(check.visited, t_game->map.height);
}
