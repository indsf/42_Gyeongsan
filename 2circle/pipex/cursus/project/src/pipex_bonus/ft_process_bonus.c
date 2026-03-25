/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 13:49:34 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/04 21:51:36 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_result	ft_struct(int fd, pid_t pid)
{
	t_result	info;

	info.fd = fd;
	info.pid = pid;
	return (info);
}

t_result	ft_process(char *cmd, char **envp, int saved_fd)
{
	int			fd[2];
	pid_t		pid;

	if (pipe(fd) == -1)
		ft_perror_exit(NULL, 0);
	pid = fork();
	if (pid == -1)
		ft_perror_exit(NULL, 0);
	if (pid == 0)
	{
		close(fd[0]);
		if (saved_fd < 0)
			exit(1);
		if (dup2(saved_fd, 0) == -1 || dup2(fd[1], 1) == -1)
		{
			ft_close(fd[1], saved_fd);
			ft_perror_exit(NULL, 1);
		}
		ft_close(fd[1], saved_fd);
		ft_cmd_excute(cmd, envp);
	}
	close(fd[1]);
	return (ft_struct(fd[0], pid));
}
