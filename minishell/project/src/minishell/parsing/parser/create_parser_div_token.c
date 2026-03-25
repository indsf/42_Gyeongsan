/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_parser_div_token.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 17:55:02 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:38:49 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*token의 연결 리스트에 파이프가 있는지 확인하는 함수*/
static int	is_checker(t_token *token)
{
	while (token)
	{
		if (token->quotes == ZERO_QUEOTES && token->cmd[0] == '|')
		{
			if (token->next == NULL)
				return (1);
			return (0);
		}
		token = token->next;
	}
	return (0);
}

/*pipe를 기준으로 앞의 token을 자르는 함수*/
static t_token	*parser_input_token(t_token **token, int *pipe_count)
{
	t_token	*result;
	t_token	*tmp;
	t_token	*prev;

	prev = NULL;
	result = *token;
	while ((*token))
	{
		if ((*token)->quotes == ZERO_QUEOTES && (*token)->cmd[0] == '|')
		{
			*pipe_count = (*token)->pipe_count;
			tmp = (*token)->next;
			token_delone((*token));
			*token = tmp;
			if (prev)
				prev->next = NULL;
			else
				return (NULL);
			return (result);
		}
		prev = (*token);
		(*token) = (*token)->next;
	}
	return (result);
}

/*token안의 pipe를 기준으로 나눠서 parser를 만드는 함수*/
t_parser	*create_parser_div_token(t_token **token)
{
	t_create_parser	cp;

	cp.result = NULL;
	cp.next_count = 0;
	while (*token)
	{
		cp.pipe_count = 0;
		cp.checker = is_checker(*token);
		cp.splited_token = parser_input_token(token, &cp.pipe_count);
		cp.new = parser_new(cp.splited_token, cp.next_count);
		cp.next_count = cp.pipe_count;
		if (!cp.new)
			return (token_clear(token), parser_clear(&cp.result), NULL);
		parser_add_back(&cp.result, cp.new);
		if (cp.checker)
		{
			cp.new = parser_new(NULL, cp.next_count);
			if (!cp.new)
				return (token_clear(token), parser_clear(&cp.result), NULL);
			parser_add_back(&cp.result, cp.new);
		}
	}
	return (cp.result);
}
