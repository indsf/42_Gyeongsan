/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:05:24 by jaehlee           #+#    #+#             */
/*   Updated: 2026/02/10 21:16:20 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "built_in.h"
# include "include.h"
# include "lexer.h"
# include "ms_struct.h"
# include "parser.h"
# include "utils.h"

extern int	g_signal_code;

/*중요한 함수들 선언*/

void		lexer_n_parser(t_data *data, char *str);

void		excute_process(t_data *data);
int			file_open(t_execve *cur);
void		multi_pipe(t_data *data);
void		multi_fork_execute(t_data *data, t_execve *exec);
void		single_pipe(t_data *data);
void		single_fork_execute(t_data *data, t_execve *exec);

int			open_heredoc(t_data *data, t_parser *parser);
int			open_redirect(t_parser *cur_parser);

void		execute_signal(void);
void		main_signal(void);
void		heredoc_signal(void);
void		reset_signal(void);

#endif
