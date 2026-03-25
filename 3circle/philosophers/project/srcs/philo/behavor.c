/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   behavor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 22:18:44 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/29 18:47:01 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	get_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		philo_printf(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->right_fork);
		philo_printf(philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_printf(philo, "has taken a fork\n");
		pthread_mutex_lock(philo->left_fork);
		philo_printf(philo, "has taken a fork\n");
	}
	return (0);
}

void	put_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	eat_simulation(t_philo *philo)
{
	philo_printf(philo, "is eating\n");
	pthread_mutex_lock(philo->meal_mutex);
	philo->last_eat = ft_now_ms();
	philo->eat_ct += 1;
	if (philo->act->must_eat > 0 && philo->full == 0
		&& philo->eat_ct >= philo->act->must_eat)
	{
		philo->full = 1;
		philo->act->finished_eat += 1;
	}
	pthread_mutex_unlock(philo->meal_mutex);
	ft_sleep(philo->act->eat, philo);
	put_fork(philo);
	if (philo->act->must_eat > 0 && philo->full)
		return (1);
	return (0);
}
