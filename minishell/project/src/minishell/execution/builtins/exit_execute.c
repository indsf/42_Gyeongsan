/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:41:13 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 20:28:27 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	num_range_check(const char *cmd)
{
	const char	p_max[20] = "9223372036854775807";
	const char	n_max[20] = "9223372036854775808";
	int			sign;
	int			len;

	sign = 1;
	if (cmd[0] == '-' || cmd[0] == '+')
	{
		if (cmd[0] == '-')
			sign *= -1;
		cmd++;
	}
	len = ft_strlen(cmd);
	if (len > 19)
		return (1);
	if (len == 19)
	{
		if (sign == 1 && ft_strcmp(cmd, p_max) > 0)
			return (1);
		else if (sign == -1 && ft_strcmp(cmd, n_max) > 0)
			return (1);
	}
	return (0);
}

static int	exit_form_check(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '-' || cmd[i] == '+')
		i++;
	while (cmd[i])
	{
		if (!(cmd[i] >= '0' && cmd[i] <= '9'))
			return (1);
		i++;
	}
	return (num_range_check(cmd));
}

int	exit_execute(t_data *data, t_execve *exec)
{
	int	i;

	i = 0;
	while (exec->cmd[i] && i < 3)
		i++;
	if (i == 1)
	{
		write(1, "exit\n", 5);
		exit_error(data, g_signal_code, 0);
	}
	else if (exit_form_check(exec->cmd[1]))
	{
		write(1, "exit\n", 5);
		error_print_middle(": numeric argument required\n", \
			2, "exit: ", exec->cmd[1]);
		exit_error(data, g_signal_code, 0);
	}
	else if (i > 2)
		return (error_print_middle("too many arguments\n", \
			0, "exit: ", NULL), 1);
	write(1, "exit\n", 5);
	exit_error(data, (unsigned char)ft_atoi(exec->cmd[1]), 0);
	return (0);
}
