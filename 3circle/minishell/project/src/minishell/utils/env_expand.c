/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expand.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/05 21:18:35 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:46:04 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand(t_env *env, char *cmd, int len)
{
	char	*env_cmd;

	env_cmd = malloc(sizeof(char) * (len));
	if (!env_cmd)
		return (NULL);
	env_cmd[--len] = '\0';
	while (len--)
		env_cmd[len] = cmd[len + 1];
	if (!ft_strcmp(env_cmd, "") || !ft_strcmp(env_cmd, "$"))
		return (free(env_cmd), ft_strdup("$"));
	else if (!ft_strcmp(env_cmd, "?"))
		return (free(env_cmd), ft_itoa(g_signal_code));
	while (env)
	{
		if (!ft_strcmp(env->key_value[0], env_cmd))
		{
			if (env->key_value[1])
				return (free(env_cmd), ft_strdup(env->key_value[1]));
			else
				return (free(env_cmd), ft_strdup(""));
		}
		env = env->next;
	}
	return (free(env_cmd), ft_strdup(""));
}

static int	is_check(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '$')
	{
		i++;
		if (cmd[i] == '$' || cmd[i] == '?')
			return (2);
		while (cmd[i])
		{
			if (cmd[i] == ' ' || cmd[i] == '\0' || cmd[i] == '$')
				break ;
			i++;
		}
	}
	return (i);
}

static char	*env_result_func(char *cmd, char *expand_str, char *env_result)
{
	char	*merge_str;
	char	*tmp;

	merge_str = ft_strjoin(cmd, expand_str);
	free(expand_str);
	if (!merge_str)
		return (free(env_result), NULL);
	tmp = env_result;
	env_result = ft_strjoin(tmp, merge_str);
	free(tmp);
	free(merge_str);
	return (env_result);
}

int	cmd_env_check(char *cmd)
{
	if (!cmd)
		return (0);
	while (*cmd)
	{
		if (*cmd == '$')
			return (1);
		cmd++;
	}
	return (0);
}

char	*env_expand(t_env *env, char *cmd)
{
	char	*env_result;
	char	*expand_str;
	int		i;
	int		len;

	env_result = NULL;
	i = -1;
	while (cmd[++i])
	{
		len = is_check(cmd + i);
		if (!len)
			continue ;
		expand_str = expand(env, cmd + i, len);
		if (!expand_str)
			return (free(env_result), NULL);
		cmd[i] = '\0';
		env_result = env_result_func(cmd, expand_str, env_result);
		if (!env_result)
			return (NULL);
		cmd += (i + len);
		i = -1;
	}
	if (*cmd)
		env_result = env_result_func(cmd, NULL, env_result);
	return (env_result);
}
