/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:42:30 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/11 21:25:40 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_dup2(int saved_fd, int write_fd, t_execve *exec)
{
	if (write_fd > 2)
	{
		if (dup2(write_fd, 1) < 0)
		{
			if (saved_fd)
				close(saved_fd);
			return (close(write_fd), 1);
		}
		close(write_fd);
	}
	if (saved_fd > 2)
	{
		if (dup2(saved_fd, 0) < 0)
			return (close(saved_fd), 1);
		close(saved_fd);
	}
	if (exec->in.fd > 2 && dup2(exec->in.fd, 0) < 0)
		return (1);
	if (exec->out.fd > 2 && dup2(exec->out.fd, 1) < 0)
		return (1);
	return (0);
}

static int	last_multi_fork_dup(t_data *data, t_execve *exec, int saved_fd,
		int *pid)
{
	*pid = fork();
	if (*pid < 0)
		exit_error(data, 0, 1);
	if (*pid == 0)
	{
		execute_signal();
		if (file_open(exec))
			return (close(saved_fd), exit_error(data, 1, 0), \
			1);
		if (set_dup2(saved_fd, 0, exec))
			exit_error(data, 0, 1);
		if (!exec->cmd)
			return (error_print_middle(": command not found\n", 0, NULL, NULL), \
					close(saved_fd), exit_error(data, 127, 0), 1);
		multi_fork_execute(data, exec);
	}
	if (saved_fd)
		close(saved_fd);
	return (0);
}

static int	first_multi_fork_dup(t_data *data, t_execve *exec, int saved_fd,
		int *pid)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) < 0)
		exit_error(data, 0, 1);
	*pid = fork();
	if (*pid < 0)
		exit_error(data, 0, 1);
	if (*pid == 0)
	{
		execute_signal();
		close(pipe_fd[0]);
		if (file_open(exec))
			return (close(saved_fd), close(pipe_fd[1]), \
			exit_error(data, 1, 0), 1);
		if (!exec->cmd)
			return (error_print_middle(": command not found\n", 0, NULL, NULL), \
			close(saved_fd), close(pipe_fd[1]), exit_error(data, 127, 0), 1);
		if (set_dup2(saved_fd, pipe_fd[1], exec))
			exit_error(data, 0, 1);
		multi_fork_execute(data, exec);
	}
	close(pipe_fd[1]);
	if (saved_fd)
		close(saved_fd);
	return (pipe_fd[0]);
}

void	multi_pipe(t_data *data)
{
	t_execve	*cur;
	int			saved_fd;
	int			pid;
	int			status;

	cur = data->exec;
	saved_fd = 0;
	reset_signal();
	while (cur)
	{
		if (cur->next)
			saved_fd = first_multi_fork_dup(data, cur, saved_fd, &pid);
		else
			last_multi_fork_dup(data, cur, saved_fd, &pid);
		cur = cur->next;
	}
	if (waitpid(pid, &status, 0) < 0)
		exit_error(data, 0, 1);
	if (WIFEXITED(status))
		g_signal_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_signal_code = WTERMSIG(status) + 128;
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
}
