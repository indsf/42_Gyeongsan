/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 16:28:40 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/29 19:11:18 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	wait_finish_loop(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->act->finish_mutex);
		if (philo->act->finish == FINISHED)
		{
			pthread_mutex_unlock(&philo->act->finish_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->act->finish_mutex);
		usleep(1000);
	}
	return (1);
}

int	handle_single_philo(t_philo *philo)
{
	if (philo->left_fork != philo->right_fork)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	philo_printf(philo, "has taken a fork\n");
	wait_finish_loop(philo);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

int	take_forks_or_stop(t_philo *philo)
{
	if (ft_check(philo))
		return (1);
	if (get_fork(philo) != 0)
		return (1);
	if (ft_check(philo))
	{
		put_fork(philo);
		return (1);
	}
	return (0);
}

int	sleep_think_or_stop(t_philo *philo)
{
	if (ft_check(philo))
		return (1);
	philo_printf(philo, "is sleeping\n");
	ft_sleep(philo->act->sleep + (philo->act->philo_num % 2) * 10, philo);
	if (ft_check(philo))
		return (1);
	philo_printf(philo, "is thinking\n");
	return (0);
}
