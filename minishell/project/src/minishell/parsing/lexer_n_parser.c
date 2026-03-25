/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_n_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:11:18 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/23 18:09:39 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser	*parser(t_data *data, t_token *token)
{
	t_parser	*parser;

	parser = create_parser_div_token(&token);
	if (!parser)
		exit_error(data, 0, 1);
	if (split_zero_quotes(parser) || env_replace(data->env, parser)
		|| split_zero_quotes(parser) || parser_check_merge(parser)
		|| trim_cmd_isspace(parser))
	{
		parser_clear(&parser);
		exit_error(data, 0, 1);
	}
	remove_space_token(parser);
	if (parser_check_form(parser))
		return (parser_clear(&parser), NULL);
	if (open_heredoc(data, parser))
		return (parser_clear(&parser), NULL);
	if (open_redirect(parser))
	{
		parser_clear(&parser);
		exit_error(data, 0, 1);
	}
	return (parser);
}

static t_token	*lexer(t_data *data, char *str)
{
	t_token	*token;
	int		check;

	if (quotes_count_check(str))
		return (error_print("Quote is not open and closed\n", 1), \
				free(str), NULL);
	token = quotes_div_token(str);
	if (!token)
		exit_error(data, 0, 1);
	check = token_div_pipe(&token);
	if (!check)
		check = token_div_redirect(&token);
	if (check)
	{
		token_clear(&token);
		exit_error(data, 0, 1);
	}
	return (token);
}

void	lexer_n_parser(t_data *data, char *str)
{
	t_execve	*result;
	t_parser	*parsing;
	t_token		*token;

	token = lexer(data, str);
	if (!token)
		return ;
	parsing = parser(data, token);
	result = translate_parser(data, parsing);
	parser_clear_exception_last_redir(&parsing);
	data->exec = result;
}
