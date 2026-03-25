/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_zero_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 21:34:05 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/06 14:03:02 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_cmd3(t_splited_token *pc)
{
	t_token	*prev;
	t_token	*token;
	t_token	*new;

	token = pc->result_token;
	while (token && token->next)
	{
		new = token_new(ft_strdup(""), 0);
		if (!new)
			return (1);
		prev = token;
		token = token->next;
		prev->next = new;
		new->next = token;
	}
	return (0);
}

static int	split_cmd2(t_token **token, t_token *cur_token, t_token *prev_token,
		t_splited_token *pc)
{
	if (split_cmd3(pc))
		return (1);
	if (pc->start)
	{
		pc->new_token = token_new(ft_strdup(""), 0);
		if (!pc->new_token)
			return (1);
		pc->new_token->next = pc->result_token;
		pc->result_token = pc->new_token;
	}
	if (pc->end)
	{
		pc->new_token = token_new(ft_strdup(""), 0);
		if (!pc->new_token)
			return (1);
		pc->last_token->next = pc->new_token;
		pc->last_token = pc->new_token;
	}
	if (!prev_token)
		*token = pc->result_token;
	else
		prev_token->next = pc->result_token;
	pc->last_token->next = cur_token->next;
	token_delone(cur_token);
	return (0);
}

static t_token	*split_cmd(t_token **token, t_token *cur_token,
		t_token *prev_token, int count)
{
	t_splited_token	pc;

	pc.cmd = cur_token->cmd;
	pc.result_token = NULL;
	pc.start = 0;
	if (ft_isspace(pc.cmd[0]))
		pc.start = 1;
	pc.end = 0;
	if (pc.cmd[0] && ft_isspace(pc.cmd[ft_strlen(pc.cmd) - 1]))
		pc.end = 1;
	pc.i = -1;
	while (++(pc.i) < count)
	{
		pc.result = splited_cmd(&(pc.cmd));
		if (!pc.result)
			return (token_clear(&(pc.result_token)), NULL);
		pc.new_token = token_new(pc.result, ZERO_QUEOTES);
		if (!pc.new_token)
			return (token_clear(&(pc.result_token)), free(pc.result), NULL);
		token_add_back(&(pc.result_token), pc.new_token);
		pc.last_token = pc.new_token;
	}
	if (split_cmd2(token, cur_token, prev_token, &pc))
		return (token_clear(&(pc.result_token)), NULL);
	return (pc.last_token);
}

static int	run_split(t_parser *cur_parser, t_token **cur_token,
		t_token *prev_token)
{
	int	count;

	if ((*cur_token)->cmd && (*cur_token)->quotes == ZERO_QUEOTES)
	{
		count = cmd_isspace_word_count((*cur_token)->cmd);
		if (count)
		{
			(*cur_token) = split_cmd(&(cur_parser->token), (*cur_token),
					prev_token, count);
			if (!(*cur_token))
				return (1);
		}
	}
	return (0);
}

int	split_zero_quotes(t_parser *parser)
{
	t_parser	*cur_parser;
	t_token		*cur_token;
	t_token		*prev_token;

	cur_parser = parser;
	while (cur_parser)
	{
		cur_token = cur_parser->token;
		prev_token = NULL;
		while (cur_token)
		{
			if (run_split(cur_parser, &cur_token, prev_token))
				return (1);
			prev_token = cur_token;
			cur_token = cur_token->next;
		}
		cur_parser = cur_parser->next;
	}
	return (0);
}
