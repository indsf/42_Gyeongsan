/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 23:04:50 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:46:45 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_isspace_word_count(char *cmd)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd[i])
	{
		while (ft_isspace(cmd[i]))
			i++;
		if (cmd[i])
			count++;
		while (cmd[i] && !ft_isspace(cmd[i]))
			i++;
	}
	return (count);
}

char	*splited_cmd(char **cmd)
{
	char	*result;
	char	*start_cmd;
	int		i;
	int		len;

	while (ft_isspace(**cmd))
		(*cmd)++;
	start_cmd = *cmd;
	len = 0;
	while (**cmd && !ft_isspace(**cmd))
	{
		(*cmd)++;
		len++;
	}
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	i = 0;
	while (i < len)
	{
		result[i] = start_cmd[i];
		i++;
	}
	return (result);
}
