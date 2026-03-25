/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_cmd_splited.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:26:08 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:46:40 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strdlup(const char *s, int len)
{
	int		i;
	char	*arr;

	i = 0;
	arr = (char *)malloc(sizeof(char) * len + 1);
	if (!arr)
		return (NULL);
	while (s[i] != '\0' && i < len)
	{
		arr[i] = s[i];
		i++;
	}
	arr[i] = '\0';
	return (arr);
}

char	**export_cmd_splited(char *cmd, char *equal)
{
	char	**new_cmd;

	if (equal)
	{
		new_cmd = malloc(sizeof(char *) * 3);
		if (!new_cmd)
			return (NULL);
		new_cmd[0] = ft_strdlup(cmd, equal - cmd);
		if (!new_cmd[0])
			return (free(new_cmd), NULL);
		new_cmd[1] = ft_strdup(equal + 1);
		if (!new_cmd[1])
			return (free(new_cmd[0]), free(new_cmd), NULL);
		new_cmd[2] = NULL;
		return (new_cmd);
	}
	new_cmd = malloc(sizeof(char *) * 2);
	if (!new_cmd)
		return (NULL);
	new_cmd[0] = ft_strdup(cmd);
	if (!new_cmd[0])
		return (free(new_cmd), NULL);
	new_cmd[1] = NULL;
	return (new_cmd);
}
