/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 19:55:59 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:15:50 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDE_H
# define INCLUDE_H

/*기본 헤더 선언*/

# include "libft.h"
# include <dirent.h>            // opendir, readdir, closedir
# include <errno.h>             // errno, 에러 처리
# include <fcntl.h>             // open, O_RDONLY, O_WRONLY, O_CREAT, O_APPEND
# include <readline/history.h>  // add_history, clear_history
# include <readline/readline.h> // readline
# include <signal.h>            // signal, sigaction, kill
# include <stdio.h>             // printf, perror
# include <stdlib.h>            // malloc, free, exit, getenv
# include <string.h>            // strerror
# include <sys/ioctl.h>         // ioctl, ttyname, ttyslot
# include <sys/stat.h>          // stat, lstat, fstat
# include <sys/types.h>         // pid_t, stat 구조체
# include <sys/wait.h>          // wait, waitpid
# include <termios.h>           // tcsetattr, tcgetattr (터미널 제어)
# include <unistd.h>

#endif