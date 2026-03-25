/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 16:28:53 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:48:54 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal_code;

void	init_data(t_data *data)
{
	char	buf[4096];
	char	*str;

	data->env = NULL;
	data->exec = NULL;
	data->home = NULL;
	data->main_env = NULL;
	data->cur = NULL;
	str = getcwd(buf, sizeof(buf));
	if (!str)
		return ;
	data->cur = ft_strjoin(str, "$ ");
}

int	main(int argc, char **argv, char **env)
{
	char	*str;
	t_data	data;

	if (argc != 1 || !(**argv))
		return (1);
	init_data(&data);
	if (!data.cur)
		return (1);
	init_env(&data, env);
	while (1)
	{
		main_signal();
		str = readline(data.cur);
		if (!str)
			break ;
		if (*str)
		{
			add_history(str);
			lexer_n_parser(&data, str);
			if (data.exec)
				excute_process(&data);
		}
	}
	write(1, "exit\n", 5);
	return (exit_error(&data, g_signal_code, 0), 0);
}
