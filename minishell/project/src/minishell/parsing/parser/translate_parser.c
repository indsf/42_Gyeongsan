/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 16:35:25 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:42:39 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_count_cmd(t_token *token)
{
	int	cnt;
	int	len;

	cnt = 0;
	len = 0;
	while (token)
	{
		if (token->quotes == ZERO_QUEOTES && \
			(token->cmd[0] == '<' || token->cmd[0] == '>'))
		{
			len++;
		}
		cnt++;
		token = token->next;
	}
	return (cnt - (len * 2));
}

static char	**token_replace_build_arrays(t_token *token)
{
	char	**result;
	int		cnt;
	int		i;

	cnt = token_count_cmd(token);
	result = malloc(sizeof(char *) * (cnt + 1));
	if (!result)
		return (NULL);
	result[cnt] = NULL;
	i = 0;
	while (i < cnt)
	{
		if (!(token->quotes == ZERO_QUEOTES && \
				(token->cmd[0] == '<' || token->cmd[0] == '>')))
		{
			result[i] = ft_strdup(token->cmd);
			if (!result[i])
				return (free_array(result), NULL);
			token = token->next;
			i++;
		}
		else
			token = token->next->next;
	}
	return (result);
}

static int	redir_translate(t_redir *new, t_redir *old)
{
	while (old && old->next)
	{
		if (old->fd > 2)
			close(old->fd);
		old->fd = 0;
		old = old->next;
	}
	if (old)
	{
		new->fd = old->fd;
		new->filename = ft_strdup(old->filename);
		if (!new->filename)
			return (1);
		new->heredoc = old->heredoc;
	}
	return (0);
}

static t_execve	*translate_execve(t_parser *parser)
{
	t_execve	*new;
	t_token		*token;
	char		**new_array;

	new = exec_new();
	if (!new)
		return (NULL);
	if (redir_translate(&(new->in), parser->in))
		return (exec_clear(&new), NULL);
	if (redir_translate(&(new->out), parser->out))
		return (exec_clear(&new), NULL);
	token = parser->token;
	while (token)
	{
		if (!(token->quotes == ZERO_QUEOTES && \
				(token->cmd[0] == '<' || token->cmd[0] == '>')))
		{
			new_array = token_replace_build_arrays(parser->token);
			if (!new_array)
				return (exec_clear(&new), NULL);
			return (new->cmd = new_array, new);
		}
		token = token->next->next;
	}
	return (new);
}

t_execve	*translate_parser(t_data *data, t_parser *parser)
{
	t_execve	*result;
	t_execve	*new;
	t_parser	*cur_parser;

	result = NULL;
	cur_parser = parser;
	while (cur_parser)
	{
		new = translate_execve(cur_parser);
		if (!new)
		{
			exec_clear(&result);
			parser_clear(&parser);
			exit_error(data, 0, 1);
		}
		exec_add_back(&result, new);
		cur_parser = cur_parser->next;
	}
	return (result);
}
