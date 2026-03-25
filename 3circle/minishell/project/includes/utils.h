/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 14:57:35 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:16:59 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "include.h"
# include "ms_struct.h"

/*추가적인 도움 함수들 선언*/

char		*splited_cmd(char **cmd);
int			cmd_isspace_word_count(char *cmd);

void		free_array(char **splited);
int			ft_strcmp(const char *s1, const char *s2);

t_redir		*redir_new(char *filename, int fd, t_heredoc heredoc);
void		redir_add_pos(t_redir **cur, t_redir *new_r, int pos);
void		redir_add_back(t_redir **cur, t_redir *new_r);
void		redir_clear(t_redir **redir);

t_parser	*parser_new(t_token *token, int pipe_count);
void		parser_clear(t_parser **parse);
void		parser_add_back(t_parser **cur, t_parser *new_p);
void		parser_clear_exception_last_redir(t_parser **parse);

void		token_delone(t_token *token);
void		token_clear(t_token **token);
t_token		*token_new(char *cmd, t_quotes type);
void		token_add_back(t_token **cur, t_token *new_t);
int			cmd_env_check(char *cmd);
char		*env_expand(t_env *env, char *cmd);

char		**export_cmd_splited(char *cmd, char *equal);
void		env_clear(t_env **env);
t_env		*env_new(char **key_value);
void		init_env(t_data *data, char **env);
void		env_back_add(t_env **env, t_env *new_e);
int			env_delone(t_env **env, const char *key);

t_execve	*exec_new(void);
void		exec_add_back(t_execve **cur, t_execve *new_e);
void		exec_clear(t_execve **exec);

void		exit_error(t_data *data, int exit_code, int mode);
int			error_print(const char *error_str, int set_error_code);
int			error_print_middle(const char *error_str, int set_error_code,
				char *cmd, char *option);
int			error_print_perror(int set_error_code, char *filename);

#endif
