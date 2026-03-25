/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:47:01 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:16:42 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "include.h"
# include "ms_struct.h"

/*parser 관련 함수 선언*/

int			env_replace(t_env *env, t_parser *parser);
t_execve	*translate_parser(t_data *data, t_parser *parser);

t_parser	*create_parser_div_token(t_token **token);

int			parser_check_form(t_parser *parser);
int			split_zero_quotes(t_parser *parser);
int			trim_cmd_isspace(t_parser *parser);
int			parser_check_merge(t_parser *parser);

void		remove_space_token(t_parser *parser);

#endif