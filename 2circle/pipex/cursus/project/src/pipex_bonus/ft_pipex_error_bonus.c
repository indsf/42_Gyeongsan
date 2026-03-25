/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_error_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:41:21 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/04 04:49:34 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_perror_exit(char *str, int err)
{
	perror(str);
	if (!err)
		exit(errno);
	exit(err);
}

void	ft_child_error(pid_t child2, pid_t wpid, int status, int *code)
{
	if (wpid == child2)
	{
		if (WIFEXITED(status))
			*code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			*code = WTERMSIG(status);
		else
			*code = 1;
	}
}

int	ft_mode(char **argv)
{
	int	mode;

	mode = 1;
	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
		mode = 2;
	return (mode);
}

void	ft_close(int out_f, int saved_fd)
{
	close(out_f);
	close(saved_fd);
}
