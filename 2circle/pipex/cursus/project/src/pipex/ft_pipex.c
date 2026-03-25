/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 19:21:37 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/03 23:18:50 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	exit_main(pid_t process)
{
	pid_t	w_pid;
	int		status;
	int		code;

	w_pid = wait(&status);
	code = 0;
	while (w_pid > 0)
	{
		child_error(process, w_pid, status, &code);
		w_pid = wait(&status);
	}
	return (code);
}

int	main(int argc, char **argv, char **envp)
{
	pid_t	process;
	int		fd[2];

	if (argc < 5)
		return (write(2, "error argc\n", 11), 1);
	if (pipe(fd) < 0)
		perror_exit(NULL, 0);
	ft_proccess_child1(argv, envp, fd);
	process = ft_proccess_child2(argv, envp, fd);
	close(fd[0]);
	close(fd[1]);
	return (exit_main(process));
}
