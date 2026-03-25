/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_proccess.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 00:42:36 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/04 21:31:27 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_proccess_child1(char **argv, char **evnp, int *fd)
{
	pid_t	pid1;
	int		infile;

	pid1 = fork();
	if (pid1 == -1)
		perror_exit(NULL, 0);
	if (pid1 == 0)
	{
		close(fd[0]);
		infile = open(argv[1], O_RDONLY);
		if (infile == -1 || dup2(infile, STDIN_FILENO) == -1 || dup2(fd[1],
				STDOUT_FILENO) == -1)
		{
			close(fd[1]);
			if (infile != -1)
				close(infile);
			perror_exit(NULL, 0);
		}
		close(fd[1]);
		close(infile);
		cmd_excute(argv[2], evnp);
	}
}

pid_t	ft_proccess_child2(char **argv, char **envp, int *fd)
{
	pid_t	pid2;
	int		outfile;

	pid2 = fork();
	if (pid2 == -1)
		perror_exit(NULL, 0);
	if (pid2 == 0)
	{
		close(fd[1]);
		outfile = (open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644));
		if (outfile == -1 || dup2(fd[0], STDIN_FILENO) == -1 || dup2(outfile,
				STDOUT_FILENO) == -1)
		{
			close(fd[0]);
			if (outfile != -1)
				close(outfile);
			perror_exit(NULL, 1);
		}
		close(fd[0]);
		close(outfile);
		cmd_excute(argv[3], envp);
	}
	return (pid2);
}
