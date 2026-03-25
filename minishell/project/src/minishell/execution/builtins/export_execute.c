/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_execute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:41:24 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:47:59 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cur_env_list_check_new(t_data *data, t_env *env, t_env *new)
{
	while (env)
	{
		if (!ft_strcmp(env->key_value[0], new->key_value[0]))
		{
			if (new->key_value[1])
			{
				free(env->key_value[1]);
				env->key_value[1] = ft_strdup(new->key_value[1]);
				env_clear(&new);
				if (!env->key_value[1])
					exit_error(data, 0, 1);
			}
			return (env_clear(&new), 1);
		}
		env = env->next;
	}
	return (0);
}

static void	env_add(t_data *data, char **new_cmd)
{
	t_env	*new;

	new = env_new(new_cmd);
	if (!new)
	{
		free_array(new_cmd);
		exit_error(data, 0, 1);
	}
	if (!cur_env_list_check_new(data, data->env, new))
		env_back_add(&(data->env), new);
}

static int	export_add_env(t_data *data, char *cmd)
{
	char	**new_cmd;
	char	*equal;
	int		i;

	if (cmd[0] >= '0' && cmd[0] <= '9')
		return (error_print_middle("\': not a valid identifier\n", 0,
				"export: `", cmd), 1);
	i = -1;
	equal = ft_strchr(cmd, '=');
	if ((equal && cmd == equal))
		return (error_print_middle("\': not a valid identifier\n", 0,
				"export: `", cmd), 1);
	while (cmd[++i] && ((equal && cmd + i < equal) || (!equal)))
		if (ft_strchr(" \t\n\r\v\f?/\\\'\"`#!@%^&*()-+{}[].,:;<>~", cmd[i]))
			return (error_print_middle("\': not a valid identifier\n", 0,
					"export: `", cmd), 1);
	new_cmd = export_cmd_splited(cmd, equal);
	if (!new_cmd)
		exit_error(data, 0, 1);
	env_add(data, new_cmd);
	return (0);
}

static void	view_export(t_data *data, int i, int write_fd)
{
	t_env	*env;

	while (1)
	{
		env = data->env;
		while (env && env->rank != i)
			env = env->next;
		if (!env)
			break ;
		if (write(write_fd, "declare -x ", 11) < 0)
			exit_error(data, 0, 1);
		if (write(write_fd, env->key_value[0], \
				ft_strlen(env->key_value[0])) < 0)
			exit_error(data, 0, 1);
		if (env->key_value[1] && (write(write_fd, "=\"", 2) < 0))
			exit_error(data, 0, 1);
		if (env->key_value[1] && (write(write_fd, env->key_value[1], \
			ft_strlen(env->key_value[1])) < 0))
			exit_error(data, 0, 1);
		if (env->key_value[1] && (write(write_fd, "\"", 1) < 0))
			exit_error(data, 0, 1);
		if (write(write_fd, "\n", 1) < 0)
			exit_error(data, 0, 1);
		i++;
	}
}

int	export_execute(t_data *data, t_execve *exec, int write_fd)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (exec->cmd[i])
		i++;
	if (i == 1)
		view_export(data, 0, write_fd);
	else
	{
		if (exec->cmd[1][0] == '-')
			return (error_print_middle("option is not allowed\n", 0, "export: ",
					NULL), 1);
		i = 0;
		while (exec->cmd[++i])
			if (export_add_env(data, exec->cmd[i]))
				check = 1;
	}
	return (check);
}
