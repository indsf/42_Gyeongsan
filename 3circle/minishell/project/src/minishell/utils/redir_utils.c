/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:33:25 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:47:01 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_clear(t_redir **redir)
{
	t_redir	*prev;

	while (*redir)
	{
		prev = *redir;
		*redir = (*redir)->next;
		if (prev->fd)
			close(prev->fd);
		free(prev);
	}
}

void	redir_add_pos(t_redir **cur, t_redir *new, int pos)
{
	int		i;
	t_redir	*cur_list;
	t_redir	*prev_list;

	if (!(*cur))
		*cur = new;
	else
	{
		cur_list = *cur;
		prev_list = NULL;
		i = 0;
		while (i < pos)
		{
			prev_list = cur_list;
			cur_list = cur_list->next;
			i++;
		}
		if (prev_list)
			prev_list->next = new;
		else
			(*cur) = new;
		new->next = cur_list;
	}
}

void	redir_add_back(t_redir **cur, t_redir *new)
{
	t_redir	*cur_list;

	if (!(*cur))
		*cur = new;
	else
	{
		cur_list = *cur;
		while (cur_list->next != NULL)
		{
			cur_list = cur_list->next;
		}
		cur_list->next = new;
	}
}

t_redir	*redir_new(char *filename, int fd, t_heredoc herdoc)
{
	t_redir	*new;

	if (!filename)
		return (NULL);
	new = malloc(sizeof(t_redir));
	if (!new)
		return (NULL);
	new->filename = filename;
	new->fd = fd;
	new->heredoc = herdoc;
	new->next = NULL;
	return (new);
}
