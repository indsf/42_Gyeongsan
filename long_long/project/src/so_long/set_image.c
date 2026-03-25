/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_image.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 21:02:14 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 22:04:29 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_image(t_game_info *t_game)
{
	int	height;
	int	width;

	t_game->image.coin = mlx_xpm_file_to_image(t_game->mlx_ptr,
			"./project/src/so_long/xpm_file/coin.xpm", &width, &height);
	t_game->image.wall = mlx_xpm_file_to_image(t_game->mlx_ptr,
			"./project/src/so_long/xpm_file/wall.xpm", &width, &height);
	t_game->image.exit = mlx_xpm_file_to_image(t_game->mlx_ptr,
			"./project/src/so_long/xpm_file/exit.xpm", &width, &height);
	t_game->image.floor = mlx_xpm_file_to_image(t_game->mlx_ptr,
			"./project/src/so_long/xpm_file/floor.xpm", &width, &height);
	t_game->image.player = mlx_xpm_file_to_image(t_game->mlx_ptr,
			"./project/src/so_long/xpm_file/player.xpm", &width, &height);
	t_game->image.open = mlx_xpm_file_to_image(t_game->mlx_ptr,
			"./project/src/so_long/xpm_file/open.xpm", &width, &height);
}

static void	put_image_to_map(t_game_info *t_game, void *img, int x, int y)
{
	mlx_put_image_to_window(t_game->mlx_ptr, t_game->win_ptr, \
	img, x * 64, y * 64);
}

void	put_image(t_game_info *t_game, int height, int width)
{
	char	image;

	image = t_game->map.map[height][width];
	if (image == '1')
		put_image_to_map(t_game, t_game->image.wall, width, height);
	else if (image == 'C')
		put_image_to_map(t_game, t_game->image.coin, width, height);
	else if (image == 'P')
		put_image_to_map(t_game, t_game->image.player, width, height);
	else if (image == 'E')
	{
		if (t_game->collect_count == t_game->map.coin)
			put_image_to_map(t_game, t_game->image.open, width, height);
		else
			put_image_to_map(t_game, t_game->image.exit, width, height);
		if (t_game->player_x == width && t_game->player_y == height)
			put_image_to_map(t_game, t_game->image.player, width, height);
	}
	else if (image == 'O')
		put_image_to_map(t_game, t_game->image.open, width, height);
	else
		put_image_to_map(t_game, t_game->image.floor, width, height);
}

void	setting_img(t_game_info *t_game)
{
	int	height;
	int	width;

	height = 0;
	while (height < t_game->map.height)
	{
		width = 0;
		while (width < t_game->map.width)
		{
			put_image(t_game, height, width);
			width++;
		}
		height++;
	}
}
