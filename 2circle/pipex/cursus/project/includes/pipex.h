/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 21:40:25 by inhlee            #+#    #+#             */
/*   Updated: 2025/08/03 23:04:07 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
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

void		perror_exit(char *str, int err);
char		*find_path(char **envp);
char		*access_cmd(char *cmd, char **envp);
void		cmd_excute(char *argv, char **envp);
void		ft_frees(char **ex_path_split);
void		ft_proccess_child1(char **argv, char **envp, int *fd);
pid_t		ft_proccess_child2(char **argv, char **envp, int *fd);
void		child_error(pid_t child2, pid_t wpid, int status, int *code);
int			exit_main(pid_t process);

#endif