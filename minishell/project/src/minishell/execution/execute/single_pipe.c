/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:13:14 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:15:16 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	single_fork_dup(t_data *data, t_execve *exec)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
	{
		execute_signal();
		if (exec->in.fd > 2)
			if (dup2(exec->in.fd, 0) < 0)
				exit_error(data, 0, 1);
		if (exec->out.fd > 2)
			if (dup2(exec->out.fd, 1) < 0)
				exit_error(data, 0, 1);
		single_fork_execute(data, exec);
	}
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		g_signal_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal_code = WTERMSIG(status) + 128;
	return (0);
}

void	single_pipe(t_data *data)
{
	t_execve	*cur;
	t_built_in	check;

	cur = data->exec;
	if (!cur->cmd || file_open(cur))
		return ;
	check = built_in(data, data->exec, data->exec->out.fd);
	reset_signal();
	if (check == NON_BUILT_IN)
	{
		if (single_fork_dup(data, cur))
			exit_error(data, 0, 1);
	}
}
