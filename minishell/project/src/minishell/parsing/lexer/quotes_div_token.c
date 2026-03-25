/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_div_token.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 21:48:12 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/07 17:08:50 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*queotes_return(char *start, int len)
{
	char	*result;
	int		i;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	i = 0;
	while (i < len)
	{
		result[i] = start[i];
		i++;
	}
	return (result);
}

static char	*quotes_split(char **str, t_quotes quotes)
{
	char	*start;
	int		i;

	i = 0;
	start = *str;
	while (**str)
	{
		if (quotes == ZERO_QUEOTES && (**str == '\"' || **str == '\''))
			return (queotes_return(start, i));
		else if (quotes == ONE_QUEOTES && **str == '\'')
		{
			(*str)++;
			return (queotes_return(start, i));
		}
		else if (quotes == TWO_QUEOTES && **str == '\"')
		{
			(*str)++;
			return (queotes_return(start, i));
		}
		i++;
		(*str)++;
	}
	return (queotes_return(start, i));
}

t_token	*quotes_div_token(char *str)
{
	char		*tmp;
	char		*free_str;
	t_token		*result;
	t_token		*new;
	t_quotes	quotes;

	result = NULL;
	free_str = str;
	while (*str)
	{
		quotes = ZERO_QUEOTES;
		if (*str == '\"')
			quotes = TWO_QUEOTES;
		else if (*str == '\'')
			quotes = ONE_QUEOTES;
		if (quotes == TWO_QUEOTES || quotes == ONE_QUEOTES)
			str++;
		tmp = quotes_split(&str, quotes);
		new = token_new(tmp, quotes);
		if (!new)
			return (free(free_str), free(tmp), token_clear(&result), NULL);
		token_add_back(&result, new);
	}
	return (free(free_str), result);
}
