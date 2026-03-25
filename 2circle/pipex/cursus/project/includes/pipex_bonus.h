/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:01:58 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/05 16:15:34 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <time.h>
# include <unistd.h>

typedef struct s_process_info
{
	pid_t	pid;
	int		fd;
}			t_result;

void		ft_perror_exit(char *str, int err);
char		*ft_find_path(char **envp);
char		*ft_access_cmd(char *cmd, char **envp);
void		ft_cmd_excute(char *argv, char **envp);
void		ft_free(char **ex_path_split);
void		read_heredoc_loop(int fd_write, char *limiter, int len);
int			ft_heredoc(char *argv, int len);
t_result	ft_struct(int fd, pid_t pid);
t_result	ft_process(char *cmd, char **envp, int saved_fd);
void		ft_child_error(pid_t child2, pid_t wpid, int status, int *code);
int			ft_kind_process(int argc, char **argv, int *i);
void		ft_close(int out_f, int saved_fd);
int			ft_mode(char **argv);
pid_t		ft_last_argc(int argc, char **argv, char **envp, int saved_fd);
int			ft_openfile(char *argv, int mode);
int			exit_main(pid_t pid, int child2);
#endif
