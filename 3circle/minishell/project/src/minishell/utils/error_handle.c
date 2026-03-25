/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/01 16:36:01 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:49:00 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, int exit_code, int mode)
{
	if (data)
	{
		env_clear(&(data->env));
		exec_clear(&(data->exec));
		free(data->home);
		free(data->cur);
	}
	if (mode)
	{
		exit_code = errno;
		perror("minishell: ");
	}
	exit(exit_code);
}

int	error_print_perror(int set_error_code, char *filename)
{
	if (set_error_code)
		g_signal_code = set_error_code;
	if (write(2, "minishell: ", 11) < 0)
		return (1);
	if (write(2, filename, ft_strlen(filename)) < 0)
		return (1);
	if (write(2, ": ", 2) < 0)
		return (1);
	perror(NULL);
	return (0);
}

int	error_print(const char *error_str, int set_error_code)
{
	if (set_error_code)
		g_signal_code = set_error_code;
	if (write(2, "minishell: ", 11) < 0)
		return (1);
	if (error_str && (write(2, error_str, ft_strlen(error_str)) < 0))
		return (1);
	return (0);
}

int	error_print_middle(const char *error_str, int set_error_code, char *cmd,
		char *option)
{
	if (set_error_code)
		g_signal_code = set_error_code;
	if (write(2, "minishell: ", 11) < 0)
		return (1);
	if (cmd && (write(2, cmd, ft_strlen(cmd)) < 0))
		return (1);
	if (option && (write(2, option, ft_strlen(option)) < 0))
		return (1);
	if (error_str && (write(2, error_str, ft_strlen(error_str)) < 0))
		return (1);
	return (0);
}
