/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_fork_execute.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 21:12:31 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/11 22:17:09 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_find_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->key_value[0], "PATH") == 0)
			return (env->key_value[1]);
		env = env->next;
	}
	return (NULL);
}

static char	*env_path(t_data *data, char *cmd, t_env *env)
{
	char		*path_join;
	char		*ans_excute;
	char		**ex_path;
	int			i;

	ex_path = ft_split(ft_find_path(env), ':');
	if (!ex_path)
		return (error_print_middle(": No such file or directory\n", \
			0, cmd, NULL), \
		exit_error(data, 127, 0), NULL);
	i = 0;
	while (ex_path[i])
	{
		path_join = ft_strjoin(ex_path[i], "/");
		ans_excute = ft_strjoin(path_join, cmd);
		free(path_join);
		if (!ans_excute)
			return (free_array(ex_path), NULL);
		else if (access(ans_excute, F_OK | X_OK) == 0)
			return (free_array(ex_path), ans_excute);
		free(ans_excute);
		i++;
	}
	return (free_array(ex_path), error_print_middle(": command not found\n", 0,
			cmd, NULL), exit_error(data, 127, 0), NULL);
}

static char	*ft_access_cmd(t_data *data, char *cmd, t_env *env)
{
	struct stat	st;

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0 && stat(cmd, &st) == 0)
		{
			if (S_ISDIR(st.st_mode))
			{
				error_print_middle(": Is a directory\n", 0, cmd, NULL);
				exit_error(data, 126, 0);
			}
			else
			{
				if (access(cmd, X_OK) == 0)
					return (cmd);
				error_print_perror(126, cmd);
				exit_error(data, 126, 0);
			}
		}
		error_print_middle(": No such file or directory\n", 0, cmd, NULL);
		exit_error(data, 127, 0);
	}
	return (env_path(data, cmd, env));
}

void	single_fork_execute(t_data *data, t_execve *exec)
{
	char	*excute_path;

	excute_path = ft_access_cmd(data, exec->cmd[0], data->env);
	if (!excute_path)
		exit_error(data, 0, 1);
	execve(excute_path, exec->cmd, data->main_env);
	exit_error(data, 0, 1);
}
