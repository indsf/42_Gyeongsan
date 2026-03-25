/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 20:04:24 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 17:03:13 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	file_open(t_execve *cur)
{
	if (cur->in.filename)
	{
		if (cur->in.heredoc != HEREDOC)
		{
			cur->in.fd = open(cur->in.filename, O_RDONLY);
			if (cur->in.fd < 0)
				return (error_print_perror(1, cur->in.filename), 1);
		}
	}
	if (cur->out.filename)
	{
		if (cur->out.heredoc == HEREDOC)
			cur->out.fd = open(cur->out.filename, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else
			cur->out.fd = open(cur->out.filename, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		if (cur->out.fd < 0)
			return (error_print_perror(1, cur->out.filename), 1);
	}
	return (0);
}
