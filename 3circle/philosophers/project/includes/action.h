/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 18:56:32 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/29 18:51:46 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTION_H
# define ACTION_H

# include "utils.h"
# include "philo.h"

int		get_fork(t_philo *philo);
void	put_fork(t_philo *philo);
int		eat_simulation(t_philo *philo);
void	ft_sleep(long long sleep, t_philo *philo);

#endif