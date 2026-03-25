/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:40:10 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:11:27 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check(char *cmd)
{
	int	i;

	if (cmd[0] != '-')
		return (0);
	i = 1;
	while (cmd[i] == 'n')
		i++;
	if (cmd[i])
		return (0);
	return (1);
}

static int	option_check(char **cmd)
{
	int	i;

	i = 1;
	while (cmd[i])
	{
		if (!check(cmd[i]))
			break ;
		i++;
	}
	return (i);
}

int	echo_execute(t_data *data, t_execve *exec, int write_fd)
{
	int	i;
	int	check;

	check = option_check(exec->cmd);
	i = check;
	while (exec->cmd[i])
	{
		if (write(write_fd, exec->cmd[i], ft_strlen(exec->cmd[i])) < 0)
			exit_error(data, 0, 1);
		if (exec->cmd[i + 1])
			if (write(write_fd, " ", 1) < 0)
				exit_error(data, 0, 1);
		i++;
	}
	if (check == 1)
		if (write(write_fd, "\n", 1) < 0)
			exit_error(data, 0, 1);
	return (0);
}
