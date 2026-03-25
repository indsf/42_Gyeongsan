/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 15:01:45 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:37:37 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*token_return(char *start, int len)
{
	t_token	*new;
	char	*result;
	int		i;

	if (!(*start) || !len)
		return (NULL);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	new = token_new(result, ZERO_QUEOTES);
	if (!new)
		return (free(result), NULL);
	return (new);
}

t_token	*div_token(t_token *token, int pos, int cut_len)
{
	t_token	*prev_token;
	t_token	*cur_token;
	t_token	*next_token;

	cur_token = token_return(token->cmd + pos, cut_len);
	cur_token->pipe_count = cut_len;
	if (!cur_token)
		return (NULL);
	prev_token = token_return(token->cmd, pos);
	next_token = token_return(token->cmd + pos + cut_len, ft_strlen(token->cmd
				+ pos + cut_len));
	if (next_token)
		cur_token->next = next_token;
	if (prev_token)
	{
		prev_token->next = cur_token;
		return (prev_token);
	}
	return (cur_token);
}

t_token	*replace_token_pipe(t_token **token, t_token *prev, t_token *cur,
		t_token *new)
{
	t_token	*new_last;
	t_token	*return_pos;

	new_last = new;
	while (new_last->next)
		new_last = new_last->next;
	new_last->next = cur->next;
	if (!prev)
		*token = new;
	else
		prev->next = new;
	token_delone(cur);
	return_pos = new;
	while (return_pos->quotes == ZERO_QUEOTES && \
			return_pos->cmd[0] != '|')
		return_pos = return_pos->next;
	return (return_pos);
}

t_token	*replace_token_redir(t_token **token, t_token *prev, t_token *cur,
		t_token *new)
{
	t_token	*new_last;
	t_token	*return_pos;

	new_last = new;
	while (new_last->next)
		new_last = new_last->next;
	new_last->next = cur->next;
	if (!prev)
		*token = new;
	else
		prev->next = new;
	token_delone(cur);
	return_pos = new;
	while (return_pos->quotes == ZERO_QUEOTES && \
			!(return_pos->cmd[0] == '<' || return_pos->cmd[0] == '>'))
		return_pos = return_pos->next;
	return (return_pos);
}
