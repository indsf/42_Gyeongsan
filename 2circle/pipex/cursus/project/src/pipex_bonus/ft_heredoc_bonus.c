/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 21:08:51 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/04 05:02:25 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	read_heredoc_loop(int fd_write, char *limiter, int len)
{
	char	*temp;

	while (1)
	{
		write(1, "pipe heredoc> ", 15);
		temp = get_next_line(0);
		if (!temp || ((ft_strncmp(temp, limiter, len)) == 0
				&& temp[len] == '\n'))
		{
			free(temp);
			break ;
		}
		if (write(fd_write, temp, ft_strlen(temp)) == -1)
		{
			free(temp);
			close(fd_write);
			get_next_line(-1);
			ft_perror_exit(NULL, 0);
		}
		free(temp);
	}
	get_next_line(-1);
}

int	ft_heredoc(char *argv, int len)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) < 0)
		ft_perror_exit(NULL, 0);
	pid = fork();
	if (pid < 0)
		ft_perror_exit(NULL, 1);
	if (pid == 0)
	{
		close(fd[0]);
		read_heredoc_loop(fd[1], argv, len);
		close(fd[1]);
		exit(EXIT_SUCCESS);
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	return (fd[0]);
}

int	exit_main(pid_t pid, int last_p)
{
	int	status;
	int	code;

	pid = wait(&status);
	code = 0;
	while (pid > 0)
	{
		ft_child_error(last_p, pid, status, &code);
		pid = wait(&status);
	}
	return (code);
}
