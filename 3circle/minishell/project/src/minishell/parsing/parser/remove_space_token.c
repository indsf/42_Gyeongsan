/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_space_token.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 14:48:25 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/06 14:59:11 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_token(t_parser *parser, t_token **cur_token,
		t_token **next_token, t_token **prev_token)
{
	(*next_token) = (*cur_token)->next;
	token_delone((*cur_token));
	if ((*prev_token))
		(*prev_token)->next = (*next_token);
	else
		parser->token = (*next_token);
	(*cur_token) = (*next_token);
}

void	remove_space_token(t_parser *parser)
{
	t_token	*cur_token;
	t_token	*next_token;
	t_token	*prev_token;

	while (parser)
	{
		cur_token = parser->token;
		prev_token = NULL;
		while (cur_token)
		{
			if (cur_token->quotes == ZERO_QUEOTES && cur_token->cmd[0] == '\0')
				remove_token(parser, &cur_token, &next_token, &prev_token);
			else
			{
				prev_token = cur_token;
				cur_token = cur_token->next;
			}
		}
		parser = parser->next;
	}
}
