/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:49:44 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:16:01 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "include.h"
# include "ms_struct.h"

/*lexer 관련 함수 선언*/

t_execve	*translate_parser(t_data *data, t_parser *parser);
int			token_div_redirect(t_token **token);
int			token_div_pipe(t_token **token);
int			quotes_count_check(char *str);
t_token		*quotes_div_token(char *str);

t_token		*div_token(t_token *token, int pos, int redirect_len);
t_token		*replace_token_pipe(t_token **token, t_token *prev, t_token *cur,
				t_token *new_t);
t_token		*replace_token_redir(t_token **token, t_token *prev, t_token *cur,
				t_token *new_t);

#endif