/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_cmd_isspace.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 20:25:36 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/06 14:45:55 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	trim_cmd(t_token *cur_token)
{
	char	*new;

	new = ft_strtrim(cur_token->cmd, " \f\n\r\t\v");
	if (!new)
		return (1);
	free(cur_token->cmd);
	cur_token->cmd = new;
	return (0);
}

int	trim_cmd_isspace(t_parser *parser)
{
	t_parser	*cur_parser;
	t_token		*cur_token;

	cur_parser = parser;
	while (cur_parser)
	{
		cur_token = cur_parser->token;
		while (cur_token)
		{
			if (cur_token->cmd && cur_token->quotes == ZERO_QUEOTES)
			{
				if (trim_cmd(cur_token))
					return (1);
			}
			cur_token = cur_token->next;
		}
		cur_parser = cur_parser->next;
	}
	return (0);
}
