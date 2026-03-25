/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 23:17:17 by inhlee            #+#    #+#             */
/*   Updated: 2025/09/01 22:03:51 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	file_check(int argc, char **argv, t_game_info *t_game)
{
	int	len;

	if (argc != 2)
		print_err(t_game, "argc error\n");
	len = ft_strlen(argv[1]);
	if (len < 4 || ft_strncmp(argv[1] + len - 4, ".ber", 4))
		print_err(t_game, "Map not .ber\n");
	t_game->map.path = ft_strdup(argv[1]);
	if (!t_game->map.path)
		print_err(t_game, "Not argv\n");
	return (0);
}

// width 확보하기
static int	read_first_line(t_game_info *t_game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (1);
	t_game->map.width = trimmed_len(line);
	if (t_game->map.width <= 0)
	{
		free(line);
		return (1);
	}
	t_game->map.line = ft_strdup(line);
	free(line);
	if (!t_game->map.line)
		return (1);
	t_game->map.height = 1;
	return (0);
}

static int	read_check_square(t_game_info *t_game, int fd)
{
	char	*line;
	int		len;
	char	*join;

	line = get_next_line(fd);
	while (line != NULL)
	{
		len = trimmed_len(line);
		if (len != t_game->map.width)
		{
			ft_printf("not_square\n");
			free(line);
			return (1);
		}
		join = ft_strjoin(t_game->map.line, line);
		free(line);
		free(t_game->map.line);
		if (!join)
			return (1);
		t_game->map.line = join;
		t_game->map.height++;
		line = get_next_line(fd);
	}
	return (0);
}

int	make_map(int argc, char **argv, t_game_info *t_game)
{
	int	fd;

	fd = -1;
	if (file_check(argc, argv, t_game) == 0)
		fd = open(t_game->map.path, O_RDONLY);
	if (fd < 0)
		return (1);
	t_game->map.height = 0;
	t_game->map.width = 0;
	t_game->map.line = NULL;
	if (read_first_line(t_game, fd) || read_check_square(t_game, fd))
	{
		close(fd);
		free_map(t_game);
		ft_printf("error\n");
		return (1);
	}
	close(fd);
	t_game->map.map = ft_split(t_game->map.line, '\n');
	free(t_game->map.line);
	t_game->map.line = NULL;
	if (!t_game->map.map)
		print_err(t_game, "Map not create\n");
	return (0);
}
