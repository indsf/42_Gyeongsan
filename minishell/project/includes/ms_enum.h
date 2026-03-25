/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_enum.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:55:37 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:16:26 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_ENUM_H
# define MS_ENUM_H

/*enum 선언*/

typedef enum e_quotes
{
	ZERO_QUEOTES = 0,
	ONE_QUEOTES = 1,
	TWO_QUEOTES = 2,
}	t_quotes;

typedef enum e_heredoc
{
	NON_HERE = 0,
	HEREDOC = 1,
}	t_heredoc;

typedef enum e_built_in
{
	NON_BUILT_IN = 0,
	BUILT_IN_ECHO = 1,
	BUILT_IN_CD = 2,
	BUILT_IN_PWD = 3,
	BUILT_IN_EXPORT = 4,
	BUILT_IN_UNSET = 5,
	BUILT_IN_ENV = 6,
	BUILT_IN_EXIT = 7,
}	t_built_in;

#endif