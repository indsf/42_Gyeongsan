/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 16:53:40 by inhlee            #+#    #+#             */
/*   Updated: 2026/02/10 21:15:41 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILT_IN_H
# define BUILT_IN_H

# include "include.h"
# include "ms_struct.h"

/*built_in 함수 선언*/

t_built_in	built_in(t_data *data, t_execve *exec, int write_fd);
int			cd_execute(t_data *data, t_execve *exec);
int			echo_execute(t_data *data, t_execve *exec, int write_fd);
int			pwd_execute(t_data *data, int write_fd);
int			unset_execute(t_data *data, t_execve *exec);
int			export_execute(t_data *data, t_execve *exec, int write_fd);
int			env_execute(t_data *data, t_execve *exec, int write_fd);
int			exit_execute(t_data *data, t_execve *exec);

#endif