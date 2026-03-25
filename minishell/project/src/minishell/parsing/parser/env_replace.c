/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 19:30:21 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:42:14 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	condition_check(t_token *cur_token)
{
	static int	redir;

	if (!cur_token->cmd)
		return (redir = 0, 0);
	if (redir == 0 && \
		(cur_token->quotes == ZERO_QUEOTES || \
			cur_token->quotes == TWO_QUEOTES) \
			&& cmd_env_check(cur_token->cmd))
		return (redir = 0, 1);
	if (cur_token->quotes == ZERO_QUEOTES && (cur_token->cmd[0] == '<'
			|| cur_token->cmd[0] == '>'))
		return (redir = 1, 0);
	if (redir == 1 && cur_token->cmd[0] && !cur_token->next)
		return (redir = 0, 0);
	if (redir == 1 && cur_token->cmd[0])
		return (redir = 2, 0);
	if (redir == 1 && !cur_token->next)
		return (redir = 0, 0);
	if (redir == 2 && (!cur_token->cmd[0] || !cur_token->next))
		return (redir = 0, 0);
	return (0);
}

int	env_replace(t_env *env, t_parser *parser)
{
	t_parser	*cur_parser;
	t_token		*cur_token;
	char		*replace_cmd;

	cur_parser = parser;
	while (cur_parser)
	{
		cur_token = cur_parser->token;
		while (cur_token)
		{
			if (condition_check(cur_token))
			{
				replace_cmd = env_expand(env, cur_token->cmd);
				if (!replace_cmd)
					return (1);
				free(cur_token->cmd);
				cur_token->cmd = replace_cmd;
			}
			cur_token = cur_token->next;
		}
		cur_parser = cur_parser->next;
	}
	return (0);
}
