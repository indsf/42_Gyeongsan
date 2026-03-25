/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:22:51 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:46:35 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_execve	*exec_new(void)
{
	t_execve	*new;

	new = malloc(sizeof(t_execve));
	if (!new)
		return (NULL);
	new->in.fd = 0;
	new->in.filename = NULL;
	new->in.heredoc = 0;
	new->in.next = NULL;
	new->out.fd = 0;
	new->out.filename = NULL;
	new->out.heredoc = 0;
	new->out.next = NULL;
	new->cmd = NULL;
	new->next = NULL;
	return (new);
}

void	exec_add_back(t_execve **cur, t_execve *new)
{
	t_execve	*cur_execve;

	if (!*cur)
		*cur = new;
	else
	{
		cur_execve = *cur;
		while (cur_execve->next != NULL)
		{
			cur_execve = cur_execve->next;
		}
		cur_execve->next = new;
	}
}

void	exec_clear(t_execve **exec)
{
	t_execve	*prev;

	while (*exec)
	{
		prev = *exec;
		*exec = (*exec)->next;
		free_array(prev->cmd);
		prev->cmd = NULL;
		free(prev->in.filename);
		free(prev->out.filename);
		if (prev->in.fd > 2)
			close(prev->in.fd);
		if (prev->out.fd > 2)
			close(prev->out.fd);
		free(prev);
	}
}
