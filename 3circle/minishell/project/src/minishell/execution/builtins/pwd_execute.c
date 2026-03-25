/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:41:27 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 19:46:56 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_execute(t_data *data, int write_fd)
{
	char	buf[4096];
	char	*str;

	str = getcwd(buf, sizeof(buf));
	if (!str)
		exit_error(data, 0, 1);
	if (write(write_fd, str, ft_strlen(str)) < 0)
		exit_error(data, 0, 1);
	if (write(write_fd, "\n", 1) < 0)
	{
		exit_error(data, 0, 1);
	}
	return (0);
}
