/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:41:21 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/04 04:05:57 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	perror_exit(char *str, int err)
{
	perror(str);
	if (!err)
		exit(1);
	exit(err);
}

void	child_error(pid_t child2, pid_t wpid, int status, int *code)
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
