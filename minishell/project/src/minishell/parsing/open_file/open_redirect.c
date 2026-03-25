/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 15:16:16 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 16:33:47 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	file_in_open(t_redir **in, char *filename, t_heredoc type, int pos)
{
	int		fd;
	t_redir	*new;

	fd = 0;
	if (type != HEREDOC)
		fd = open(filename, O_RDONLY);
	if (fd > 0)
		close(fd);
	new = redir_new(filename, 0, type);
	if (!new)
		return (1);
	redir_add_pos(in, new, pos);
	if (fd < 0)
		return (redir_clear(&(new->next)), -1);
	return (0);
}

static int	file_out_open(t_redir **out, char *filename, t_heredoc type)
{
	int		fd;
	t_redir	*new;

	fd = 0;
	if (type == HEREDOC)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > 0)
		close(fd);
	new = redir_new(filename, 0, type);
	if (!new)
		return (1);
	redir_add_back(out, new);
	if (fd < 0)
		return (-1);
	return (0);
}

static t_heredoc	heredoc_check(char left, char right)
{
	if (left == right)
		return (HEREDOC);
	return (NON_HERE);
}

int	in_out_open(t_parser *cur_parser, t_token *cur_token, int pos)
{
	int	check;

	check = 0;
	if (cur_token->quotes != ZERO_QUEOTES)
		return (0);
	if (cur_token->cmd[0] == '<')
	{
		if (cur_token->cmd[1] != '<')
			check = file_in_open(&(cur_parser->in), cur_token->next->cmd,
					heredoc_check(cur_token->cmd[0], cur_token->cmd[1]), pos);
	}
	else if (cur_token->cmd[0] == '>')
	{
		check = file_out_open(&(cur_parser->out), cur_token->next->cmd,
				heredoc_check(cur_token->cmd[0], cur_token->cmd[1]));
	}
	return (check);
}

int	open_redirect(t_parser *cur_parser)
{
	int		check;
	t_token	*cur_token;
	int		pos;

	while (cur_parser)
	{
		cur_token = cur_parser->token;
		pos = 0;
		while (cur_token)
		{
			check = in_out_open(cur_parser, cur_token, pos);
			if (check == 1)
				return (1);
			else if (check == -1)
				break ;
			if (cur_token->cmd[0] == '<')
				pos++;
			cur_token = cur_token->next;
		}
		cur_parser = cur_parser->next;
	}
	return (0);
}
