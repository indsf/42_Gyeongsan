/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 21:43:06 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 16:12:37 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_press(int keycode, void *param)
{
	t_game_info	*t_game;

	t_game = (t_game_info *)param;
	if (keycode == KEY_W)
		move_w(t_game);
	else if (keycode == KEY_S)
		move_s(t_game);
	else if (keycode == KEY_A)
		move_a(t_game);
	else if (keycode == KEY_D)
		move_d(t_game);
	else if (keycode == KEY_ESC)
		exit_game(t_game);
	return (0);
}

void	move_w(t_game_info *t_game)
{
	int	x;
	int	y;
	int	ny;

	x = t_game->player_x;
	y = t_game->player_y;
	ny = y - 1;
	if (t_game->map.map[ny][x] == 'C')
		t_game->collect_count++;
	if (t_game->map.map[ny][x] == 'E')
	{
		if (t_game->collect_count == t_game->map.coin)
			clear_game(t_game);
	}
	if (t_game->map.map[ny][x] != '1')
	{
		if (t_game->map.map[y][x] != 'E')
			t_game->map.map[y][x] = '0';
		if (t_game->map.map[ny][x] != 'E')
			t_game->map.map[ny][x] = 'P';
		t_game->player_y = ny;
		t_game->move_count++;
		ft_printf("%d\n", t_game->move_count);
		setting_img(t_game);
	}
}

void	move_a(t_game_info *t_game)
{
	int	x;
	int	y;
	int	nx;

	x = t_game->player_x;
	y = t_game->player_y;
	nx = x - 1;
	if (t_game->map.map[y][nx] == 'C')
		t_game->collect_count++;
	if (t_game->map.map[y][nx] == 'E')
	{
		if (t_game->collect_count == t_game->map.coin)
			clear_game(t_game);
	}
	if (t_game->map.map[y][nx] != '1')
	{
		if (t_game->map.map[y][x] != 'E')
			t_game->map.map[y][x] = '0';
		if (t_game->map.map[y][nx] != 'E')
			t_game->map.map[y][nx] = 'P';
		t_game->player_x = nx;
		t_game->move_count++;
		ft_printf("%d\n", t_game->move_count);
		setting_img(t_game);
	}
}

void	move_s(t_game_info *t_game)
{
	int	x;
	int	y;
	int	ny;

	x = t_game->player_x;
	y = t_game->player_y;
	ny = y + 1;
	if (t_game->map.map[ny][x] == 'C')
		t_game->collect_count++;
	if (t_game->map.map[ny][x] == 'E')
	{
		if (t_game->collect_count == t_game->map.coin)
			clear_game(t_game);
	}
	if (t_game->map.map[ny][x] != '1')
	{
		if (t_game->map.map[y][x] != 'E')
			t_game->map.map[y][x] = '0';
		if (t_game->map.map[ny][x] != 'E')
			t_game->map.map[ny][x] = 'P';
		t_game->player_y = ny;
		t_game->move_count++;
		ft_printf("%d\n", t_game->move_count);
		setting_img(t_game);
	}
}

void	move_d(t_game_info *t_game)
{
	int	x;
	int	y;
	int	nx;

	x = t_game->player_x;
	y = t_game->player_y;
	nx = x + 1;
	if (t_game->map.map[y][nx] == 'C')
		t_game->collect_count++;
	if (t_game->map.map[y][nx] == 'E')
	{
		if (t_game->collect_count == t_game->map.coin)
			clear_game(t_game);
	}
	if (t_game->map.map[y][nx] != '1')
	{
		if (t_game->map.map[y][x] != 'E')
			t_game->map.map[y][x] = '0';
		if (t_game->map.map[y][nx] != 'E')
			t_game->map.map[y][nx] = 'P';
		t_game->player_x = nx;
		t_game->move_count++;
		ft_printf("%d\n", t_game->move_count);
		setting_img(t_game);
	}
}
