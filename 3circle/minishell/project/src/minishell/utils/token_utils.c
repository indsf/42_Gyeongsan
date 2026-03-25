/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:45:19 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/02 19:26:36 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_delone(t_token *token)
{
	if (token)
	{
		free(token->cmd);
		free(token);
	}
}

void	token_clear(t_token **token)
{
	t_token	*prev;

	while (*token)
	{
		prev = *token;
		*token = (*token)->next;
		free(prev->cmd);
		free(prev);
	}
}

void	token_add_back(t_token **cur, t_token *new)
{
	t_token	*cur_list;

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

t_token	*token_new(char *cmd, t_quotes type)
{
	t_token	*new;

	if (!cmd)
		return (NULL);
	new = malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->quotes = type;
	new->next = NULL;
	new->pipe_count = 0;
	return (new);
}
