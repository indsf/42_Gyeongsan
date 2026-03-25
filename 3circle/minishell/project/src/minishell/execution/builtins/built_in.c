/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:41:26 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:08:11 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_built_in	built_in_check(t_execve *exec)
{
	char	**cmd;

	cmd = exec->cmd;
	if (!ft_strcmp(cmd[0], "echo"))
		return (BUILT_IN_ECHO);
	else if (!ft_strcmp(cmd[0], "cd"))
		return (BUILT_IN_CD);
	else if (!ft_strcmp(cmd[0], "pwd"))
		return (BUILT_IN_PWD);
	else if (!ft_strcmp(cmd[0], "export"))
		return (BUILT_IN_EXPORT);
	else if (!ft_strcmp(cmd[0], "unset"))
		return (BUILT_IN_UNSET);
	else if (!ft_strcmp(cmd[0], "env"))
		return (BUILT_IN_ENV);
	else if (!ft_strcmp(cmd[0], "exit"))
		return (BUILT_IN_EXIT);
	else
		return (NON_BUILT_IN);
}

t_built_in	built_in(t_data *data, t_execve *exec, int write_fd)
{
	t_built_in	type;
	int			exit_code;

	type = built_in_check(exec);
	exit_code = 0;
	if (!write_fd)
		write_fd = 1;
	if (type == NON_BUILT_IN)
		return (type);
	else if (type == BUILT_IN_ECHO)
		exit_code = echo_execute(data, exec, write_fd);
	else if (type == BUILT_IN_CD)
		exit_code = cd_execute(data, exec);
	else if (type == BUILT_IN_PWD)
		exit_code = pwd_execute(data, write_fd);
	else if (type == BUILT_IN_EXPORT)
		exit_code = export_execute(data, exec, write_fd);
	else if (type == BUILT_IN_UNSET)
		exit_code = unset_execute(data, exec);
	else if (type == BUILT_IN_ENV)
		exit_code = env_execute(data, exec, write_fd);
	else if (type == BUILT_IN_EXIT)
		exit_code = exit_execute(data, exec);
	g_signal_code = exit_code;
	return (type);
}
