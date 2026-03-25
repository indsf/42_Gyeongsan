/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:41:19 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 19:57:53 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_pwd(t_data *data)
{
	char	buf[4096];
	char	*str;

	str = getcwd(buf, sizeof(buf));
	if (!str)
		exit_error(data, 0, 1);
	if (data->cur)
		free(data->cur);
	data->cur = ft_strjoin(str, "$ ");
	if (!data->cur)
		exit_error(data, 0, 1);
}

int	cd_execute(t_data *data, t_execve *exec)
{
	int	i;
	int	ch;

	i = 0;
	while (exec->cmd[i] && i < 3)
		i++;
	if (i > 2)
		return (error_print_middle("too many arguments\n", 0, "cd: ", NULL), 1);
	else if (i == 2)
	{
		if (exec->cmd[1][0] == '-')
			return (error_print_middle("option is not allowed\n", 0, "cd: ",
					NULL), 1);
		ch = chdir(exec->cmd[1]);
		if (ch)
			return (error_print_perror(0, exec->cmd[1]), 1);
	}
	else
	{
		ch = chdir(data->home);
		if (ch)
			return (error_print_perror(0, exec->cmd[1]), 1);
	}
	set_pwd(data);
	return (0);
}
