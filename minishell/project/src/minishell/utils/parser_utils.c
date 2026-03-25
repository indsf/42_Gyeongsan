/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 17:45:19 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:46:53 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parser	*parser_new(t_token *token, int pipe_count)
{
	t_parser	*new;

	new = malloc(sizeof(t_parser));
	if (!new)
		return (NULL);
	new->in = NULL;
	new->out = NULL;
	new->next = NULL;
	new->token = token;
	new->pipe_count = pipe_count;
	return (new);
}

void	parser_add_back(t_parser **cur, t_parser *new)
{
	t_parser	*cur_parser;

	if (!*cur)
		*cur = new;
	else
	{
		cur_parser = *cur;
		while (cur_parser->next != NULL)
		{
			cur_parser = cur_parser->next;
		}
		cur_parser->next = new;
	}
}

void	parser_clear(t_parser **parse)
{
	t_parser	*prev;

	while (*parse)
	{
		prev = *parse;
		*parse = (*parse)->next;
		token_clear(&(prev->token));
		redir_clear(&(prev->in));
		redir_clear(&(prev->out));
		free(prev);
	}
}

static void	redir_clear_exception_last(t_redir *cur_r)
{
	t_redir	*prev_r;

	while (cur_r)
	{
		prev_r = cur_r;
		cur_r = cur_r->next;
		if (cur_r && prev_r->fd)
			close(prev_r->fd);
		free(prev_r);
	}
}

void	parser_clear_exception_last_redir(t_parser **parse)
{
	t_parser	*prev;

	while (*parse)
	{
		prev = *parse;
		*parse = (*parse)->next;
		token_clear(&(prev->token));
		redir_clear_exception_last(prev->in);
		redir_clear_exception_last(prev->out);
		free(prev);
	}
}
