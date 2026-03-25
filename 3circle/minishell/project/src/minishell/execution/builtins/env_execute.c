/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:41:05 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:15:58 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	view_env(t_data *data, int write_fd)
{
	t_env	*env;

	env = data->env;
	while (env)
	{
		if (env->key_value[1])
		{
			if (write(write_fd, env->key_value[0],
					ft_strlen(env->key_value[0])) < 0)
				exit_error(data, 0, 1);
			if (env->key_value[1] && (write(write_fd, "=", 1) < 0))
				exit_error(data, 0, 1);
			if (env->key_value[1] && \
				(write(write_fd, env->key_value[1], \
							ft_strlen(env->key_value[1])) < 0))
				exit_error(data, 0, 1);
			if (write(write_fd, "\n", 1) < 0)
				exit_error(data, 0, 1);
		}
		env = env->next;
	}
}

int	env_execute(t_data *data, t_execve *exec, int write_fd)
{
	int	len;

	len = 0;
	while (exec->cmd[len] && len < 2)
		len++;
	if (len != 1)
	{
		if (exec->cmd[1][0] == '-')
			return (error_print_middle("option is not allowed\n", 0, "export: ",
					NULL), 1);
		return (error_print_middle("too many arguments\n", 0, "env: ", NULL),
			1);
	}
	view_env(data, write_fd);
	return (0);
}
