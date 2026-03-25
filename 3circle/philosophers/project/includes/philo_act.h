/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:29:17 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/29 18:44:36 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ACT_H
# define PHILO_ACT_H

# include "philo.h"

int	wait_finish_loop(t_philo *philo);
int	handle_single_philo(t_philo *philo);
int	take_forks_or_stop(t_philo *philo);
int	sleep_think_or_stop(t_philo *philo);

#endif