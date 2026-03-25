/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_div_pipe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:03:05 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:44:48 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_len(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == '|' && i < 2)
		i++;
	return (i);
}

static int	pipe_function_execute(t_token **token, t_lexer *lexer)
{
	lexer->len = pipe_len(&(lexer->cur->cmd[lexer->i]));
	lexer->new = div_token(lexer->cur, lexer->i, lexer->len);
	if (!lexer->new)
		return (1);
	lexer->cur = replace_token_pipe(token, lexer->prev, lexer->cur, lexer->new);
	return (0);
}

int	token_div_pipe(t_token **token)
{
	t_lexer	lexer;
	int		checker;

	lexer.cur = *token;
	lexer.prev = NULL;
	while (lexer.cur)
	{
		lexer.i = -1;
		while (lexer.cur->quotes == ZERO_QUEOTES && lexer.cur->cmd[++lexer.i])
		{
			if (lexer.cur->cmd[lexer.i] == '|')
			{
				checker = pipe_function_execute(token, &lexer);
				if (checker)
					return (checker);
				break ;
			}
		}
		lexer.prev = lexer.cur;
		lexer.cur = lexer.cur->next;
	}
	return (0);
}
