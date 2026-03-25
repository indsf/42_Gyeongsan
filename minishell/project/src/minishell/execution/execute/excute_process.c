/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   excute_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 19:48:55 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/11 21:28:37 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	excute_process(t_data *data)
{
	if (data->exec->next)
		multi_pipe(data);
	else
		single_pipe(data);
	exec_clear(&(data->exec));
}
