/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 18:52:07 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/02 18:00:02 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroy_images(t_game_info *game)
{
	if (game->image.coin)
		mlx_destroy_image(game->mlx_ptr, game->image.coin);
	if (game->image.wall)
		mlx_destroy_image(game->mlx_ptr, game->image.wall);
	if (game->image.exit)
		mlx_destroy_image(game->mlx_ptr, game->image.exit);
	if (game->image.floor)
		mlx_destroy_image(game->mlx_ptr, game->image.floor);
	if (game->image.player)
		mlx_destroy_image(game->mlx_ptr, game->image.player);
	if (game->image.open)
		mlx_destroy_image(game->mlx_ptr, game->image.open);
}

void	game_init(int argc, char **argv, t_game_info *t_game)
{
	ft_bzero(t_game, sizeof(t_game_info));
	t_game->mlx_ptr = mlx_init();
	if (make_map(argc, argv, t_game))
		print_err(t_game, "Map load failed\n");
	map_check(t_game);
	init_player(t_game);
	check_path(t_game);
	set_image(t_game);
	t_game->win_ptr = mlx_new_window(t_game->mlx_ptr, t_game->map.width * 64,
			t_game->map.height * 64, "so_long");
	setting_img(t_game);
}

int	main(int argc, char **argv)
{
	t_game_info	*t_game;
	
	t_game = malloc(sizeof(t_game_info));
	game_init(argc, argv, t_game);
	mlx_key_hook(t_game->win_ptr, key_press, t_game);
	mlx_hook(t_game->win_ptr, X_EVENT_KEY_EXIT, 0, exit_game, t_game);
	mlx_loop(t_game->mlx_ptr);
	return (0);
}
