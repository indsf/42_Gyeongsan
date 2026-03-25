/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:54:51 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 22:00:40 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	clear_game(t_game_info *t_game)
{
	t_game->move_count++;
	ft_printf("Congratulations! You have %d\n", t_game->move_count);
	exit_game(t_game);
	return (0);
}

int	exit_game(t_game_info *t_game)
{
	destroy_images(t_game);
	if (t_game->win_ptr)
		mlx_destroy_window(t_game->mlx_ptr, t_game->win_ptr);
	if (t_game->mlx_ptr)
	{
		mlx_destroy_display(t_game->mlx_ptr);
		free(t_game->mlx_ptr);
	}
	free_map(t_game);
	free(t_game);
	write(1, "Game exit\n", 10);
	exit(0);
	return (0);
}

void	print_err(t_game_info *t_game, const char *msg)
{
	if (t_game)
	{
		free_map(t_game);
		if (t_game->mlx_ptr)
		{
			mlx_destroy_display(t_game->mlx_ptr);
			free(t_game->mlx_ptr);
			t_game->mlx_ptr = NULL;
		}
		free(t_game);
	}
	write(2, "Error\n", 6);
	if (msg)
		write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}
