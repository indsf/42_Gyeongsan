/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_count_chekr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 20:21:37 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/04 20:42:26 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_quotes(char **str, char quotes)
{
	(*str)++;
	while (**str)
	{
		if ((**str) == quotes)
			return ;
		(*str)++;
	}
}

int	quotes_count_check(char *str)
{
	while (*str)
	{
		if (*str == '\"' || *str == '\'')
		{
			close_quotes(&str, *str);
			if (!(*str))
				return (1);
		}
		str++;
	}
	return (0);
}
