/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:57:49 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:45:52 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ms_sigint(int num)
{
	if (num)
	{
		g_signal_code = 130;
		rl_on_new_line();
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_redisplay();
	}
}

void	main_signal(void)
{
	signal(SIGINT, ms_sigint);
	signal(SIGQUIT, SIG_IGN);
}
