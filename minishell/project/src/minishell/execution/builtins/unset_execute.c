/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 15:41:29 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/09 14:33:15 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_execute(t_data *data, t_execve *exec)
{
	t_env	*cur;
	int		remove_rank;
	int		i;

	i = 0;
	if (exec->cmd[1] && exec->cmd[1][0] == '-')
		return (error_print_middle("option is not allowed\n", 0, "unset: ",
				NULL), 1);
	while (exec->cmd[++i])
	{
		remove_rank = env_delone(&(data->env), exec->cmd[i]);
		cur = data->env;
		while (cur)
		{
			if (cur->rank > remove_rank)
				cur->rank--;
			cur = cur->next;
		}
	}
	return (0);
}
