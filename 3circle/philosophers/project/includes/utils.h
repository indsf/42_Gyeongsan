/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 21:49:42 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/30 19:07:21 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "action.h"
# include "init.h"
# include "philo.h"
# include "philo_act.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int			ft_atoi(const char *nptr);
int			philo_printf(t_philo *philo, const char *str);
void		pthread_destroy_all(t_action *action);
long long	ft_now_ms(void);
int			ft_check(t_philo *philo);
void		die_check_printf(t_action *act, int p_id);
void		set_finish(t_action *act);
int			ft_finish(t_action *act);
#endif