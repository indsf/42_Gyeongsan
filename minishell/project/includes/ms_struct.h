/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_struct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:56:01 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:48:50 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MS_STRUCT_H
# define MS_STRUCT_H

# include "ms_enum.h"

/*구조체 선언*/

typedef struct s_redir
{
	char			*filename;
	t_heredoc		heredoc;
	int				fd;
	struct s_redir	*next;
}					t_redir;

typedef struct s_token
{
	char			*cmd;
	t_quotes		quotes;
	int				pipe_count;
	struct s_token	*next;
}					t_token;

typedef struct s_parser
{
	t_redir			*in;
	t_redir			*out;
	t_token			*token;
	int				pipe_count;
	struct s_parser	*next;
}					t_parser;

typedef struct s_execve
{
	t_redir			in;
	t_redir			out;
	char			**cmd;
	struct s_execve	*next;
}					t_execve;

typedef struct s_env
{
	char			**key_value;
	int				rank;
	struct s_env	*next;
}					t_env;

typedef struct s_data
{
	t_execve		*exec;
	t_env			*env;
	char			**main_env;
	char			*home;
	char			*cur;
}					t_data;

typedef struct s_lexer
{
	t_token			*new;
	t_token			*cur;
	t_token			*prev;
	int				i;
	int				len;
}					t_lexer;

typedef struct s_create_parser
{
	t_parser		*result;
	t_parser		*new;
	t_token			*splited_token;
	int				pipe_count;
	int				next_count;
	int				checker;
}					t_create_parser;

typedef struct s_splited_token
{
	t_token			*result_token;
	t_token			*last_token;
	t_token			*new_token;
	char			*result;
	char			*cmd;
	int				start;
	int				end;
	int				i;
}					t_splited_token;

#endif