/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 15:09:24 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:46:17 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_delone(t_env **env, const char *key)
{
	t_env	*cur;
	t_env	*prev;
	int		rank;

	cur = *env;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->key_value[0], key))
		{
			rank = cur->rank;
			if (prev)
				prev->next = cur->next;
			else
				*env = cur->next;
			free_array(cur->key_value);
			free(cur);
			return (rank);
		}
		prev = cur;
		cur = cur->next;
	}
	return (-1);
}

void	env_clear(t_env **env)
{
	t_env	*prev;

	while (*env)
	{
		prev = *env;
		*env = (*env)->next;
		free_array(prev->key_value);
		free(prev);
	}
}

void	env_back_add(t_env **env, t_env *new)
{
	t_env	*cur_execve;
	t_env	*prev_execve;

	if (!*env)
		*env = new;
	else
	{
		cur_execve = *env;
		prev_execve = NULL;
		while (cur_execve)
		{
			if (ft_strcmp(cur_execve->key_value[0], new->key_value[0]) > 0)
				cur_execve->rank++;
			else
				new->rank++;
			prev_execve = cur_execve;
			cur_execve = cur_execve->next;
		}
		prev_execve->next = new;
	}
}

t_env	*env_new(char **key_value)
{
	t_env	*new;

	if (!key_value)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key_value = key_value;
	new->rank = 0;
	new->next = NULL;
	return (new);
}

void	init_env(t_data *data, char **env)
{
	char	**splited;
	t_env	*new;
	int		i;

	i = -1;
	data->main_env = env;
	while (env[++i])
	{
		splited = export_cmd_splited(env[i], ft_strchr(env[i], '='));
		if (!splited)
			exit_error(data, 0, 1);
		new = env_new(splited);
		if (!new)
		{
			free_array(splited);
			exit_error(data, 0, 1);
		}
		env_back_add(&(data->env), new);
		if (!ft_strcmp(splited[0], "HOME"))
		{
			data->home = ft_strdup(splited[1]);
			if (!data->home)
				exit_error(data, 0, 1);
		}
	}
}
