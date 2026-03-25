/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 18:43:52 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 17:12:43 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "ft_printf.h"
# include "get_next_line.h"
# include "mlx.h"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_EXIT 17

typedef enum e_key
{
	KEY_W = 119,
	KEY_S = 115,
	KEY_A = 97,
	KEY_D = 100,
	KEY_ESC = 65307
}			t_key;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		player;
	int		coin;
	int		door;
	char	*line;
	char	*path;
	int		valid_path;
}			t_map;

typedef struct s_check
{
	int		y;
	int		x;
	int		collectible;
	int		**visited;
}			t_check;

typedef struct s_image
{
	void	*coin;
	void	*player;
	void	*floor;
	void	*wall;
	void	*open;
	void	*exit;
}			t_image;

typedef struct s_game_info
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		player_x;
	int		player_y;
	int		door_x;
	int		door_y;
	int		move_count;
	int		collect_count;
	t_map	map;
	t_image	image;
}			t_game_info;

// set_image
void		set_image(t_game_info *image);
void		setting_img(t_game_info *t_game);
void		put_image(t_game_info *game, int height, int width);

// map_parse
int			make_map(int argc, char **argv, t_game_info *t_game);

// check_map
void		map_check(t_game_info *t_game);

// find_path
void		check_path(t_game_info *t_game);

// find_record
void		init_player(t_game_info *t_game);

// so_long_utils
void		free_map(t_game_info *t_game);
size_t		trimmed_len(const char *s);

// so_long
void		destroy_images(t_game_info *game);
void		game_init(int argc, char **argv, t_game_info *t_game);

// error_check
int			exit_game(t_game_info *t_game);
void		print_err(t_game_info *t_game, const char *msg);
int			clear_game(t_game_info *t_game);

// play_move
int			key_press(int keycode, void *param);
void		move_w(t_game_info *t_game);
void		move_a(t_game_info *t_game);
void		move_s(t_game_info *t_game);
void		move_d(t_game_info *t_game);

#endif
