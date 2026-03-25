/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check_form.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 17:55:13 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/08 15:55:18 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	rp_error_print(char const *error_str, int len)
{
	error_print("syntax error near unexpected token ", 2);
	write(2, "`", 1);
	write(2, error_str, len);
	write(2, "\'\n", 2);
}

static int	pipe_form_check(t_parser *cur_parser, t_parser *parser)
{
	if (!cur_parser->token)
	{
		if (parser == cur_parser && !cur_parser->next)
			return (0);
		if (!cur_parser->next)
		{
			if (cur_parser->pipe_count == 2)
				return (rp_error_print("||", 2), 1);
			else if (cur_parser->pipe_count == 1)
				return (rp_error_print("|", 1), 1);
		}
		else
		{
			if (cur_parser->next->pipe_count == 2)
				return (rp_error_print("||", 2), 1);
			else if (cur_parser->next->pipe_count == 1)
				return (rp_error_print("|", 1), 1);
		}
	}
	return (0);
}

static int	redir_form_check(t_token *cur_token, t_parser *cur_parser)
{
	int	len;

	if (!cur_token->cmd || cur_token->quotes != ZERO_QUEOTES)
		return (0);
	if (!(cur_token->cmd[0] == '<' || cur_token->cmd[0] == '>'))
		return (0);
	len = ft_strlen(cur_token->cmd);
	if (len > 2)
		return (rp_error_print(&(cur_token->cmd[2]), 2), 1);
	if (len == 2 && cur_token->cmd[0] != cur_token->cmd[1])
		return (rp_error_print("newline", 7), 1);
	if (!cur_token->next || !cur_token->next->cmd)
	{
		if (!cur_parser->next)
			return (rp_error_print("newline", 7), 1);
		if (cur_parser->next->pipe_count == 2)
			return (rp_error_print("||", 2), 1);
		else if (cur_parser->next->pipe_count == 1)
			return (rp_error_print("|", 1), 1);
	}
	if (cur_token->next->quotes != ZERO_QUEOTES)
		return (0);
	if (cur_token->next->cmd[0] == '<' || cur_token->next->cmd[0] == '>')
		return (rp_error_print(cur_token->next->cmd, 2), 1);
	return (0);
}

int	parser_check_form(t_parser *parser)
{
	t_parser	*cur_parser;
	t_token		*cur_token;

	cur_parser = parser;
	while (cur_parser)
	{
		cur_token = cur_parser->token;
		while (cur_token)
		{
			if (redir_form_check(cur_token, cur_parser))
				return (1);
			cur_token = cur_token->next;
		}
		if (pipe_form_check(cur_parser, parser))
			return (1);
		cur_parser = cur_parser->next;
	}
	return (0);
}
