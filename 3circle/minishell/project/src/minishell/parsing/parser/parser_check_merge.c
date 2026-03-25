/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_merge.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 17:18:29 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:41:28 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_check_cmd(t_token *token)
{
	char	*s;

	s = token->cmd;
	if (!s)
		return (0);
	if (token->quotes == ZERO_QUEOTES && \
		(s[0] == '<' || s[0] == '>'))
		return (1);
	return (0);
}

static int	merge_quotes_check(t_token *token)
{
	int	i;

	if (!token || !token->next || !token->cmd || !token->next->cmd)
		return (0);
	i = 0;
	while (token->quotes == ZERO_QUEOTES && token->cmd[i]
		&& ft_isspace(token->cmd[i]))
		i++;
	if (token->quotes == ZERO_QUEOTES && !token->cmd[i])
		return (0);
	i = 0;
	while (token->next->quotes == ZERO_QUEOTES && token->next->cmd[i]
		&& ft_isspace(token->next->cmd[i]))
		i++;
	if (token->next->quotes == ZERO_QUEOTES && !token->next->cmd[i])
		return (0);
	if (redirect_check_cmd(token) || redirect_check_cmd(token->next))
		return (0);
	if (token->quotes == ZERO_QUEOTES && token->cmd[0] == '\0')
		return (0);
	if (token->next->quotes == ZERO_QUEOTES && token->next->cmd[0] == '\0')
		return (0);
	return (1);
}

static t_token	*merge_concat(t_token **token, t_token *cur_token,
		t_token *prev_token)
{
	t_token	*next_token;
	t_token	*new_token;
	char	*new_cmd;

	next_token = cur_token->next;
	new_cmd = ft_strjoin(cur_token->cmd, next_token->cmd);
	if (!new_cmd)
		return (NULL);
	new_token = token_new(new_cmd, 2);
	if (!new_token)
		return (free(new_cmd), NULL);
	if (!prev_token)
		(*token) = new_token;
	else
		prev_token->next = new_token;
	new_token->next = next_token->next;
	token_delone(cur_token);
	token_delone(next_token);
	return (new_token);
}

int	parser_check_merge(t_parser *parser)
{
	t_parser	*cur_parser;
	t_token		*cur_token;
	t_token		*prev_token;

	cur_parser = parser;
	while (cur_parser)
	{
		cur_token = cur_parser->token;
		prev_token = NULL;
		while (cur_token && cur_token->next)
		{
			if (merge_quotes_check(cur_token))
			{
				cur_token = merge_concat(&(cur_parser->token), cur_token,
						prev_token);
				if (!cur_token)
					return (1);
				continue ;
			}
			prev_token = cur_token;
			cur_token = cur_token->next;
		}
		cur_parser = cur_parser->next;
	}
	return (0);
}
