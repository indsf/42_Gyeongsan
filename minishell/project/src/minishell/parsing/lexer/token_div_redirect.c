/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_div_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:24:36 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/06 14:03:02 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_len(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == '<' || cmd[i] == '>')
		i++;
	return (i);
}

static int	redir_function_execute(t_token **token, t_lexer *lexer)
{
	lexer->len = redirect_len(&(lexer->cur->cmd[lexer->i]));
	lexer->new = div_token(lexer->cur, lexer->i, lexer->len);
	if (!lexer->new)
		return (1);
	lexer->cur = replace_token_redir(token, lexer->prev, lexer->cur,
			lexer->new);
	return (0);
}

int	token_div_redirect(t_token **token)
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
			if (lexer.cur->cmd[lexer.i] == '<'
				|| lexer.cur->cmd[lexer.i] == '>')
			{
				checker = redir_function_execute(token, &lexer);
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
