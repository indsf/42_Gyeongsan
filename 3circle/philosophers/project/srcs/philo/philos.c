/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 20:23:17 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/29 19:02:23 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_sleep(long long sleep, t_philo *philo)
{
	long long	start;

	start = ft_now_ms();
	if (start < 0)
		return ;
	while (1)
	{
		pthread_mutex_lock(&philo->act->finish_mutex);
		if (philo->act->finish == FINISHED)
		{
			pthread_mutex_unlock(&philo->act->finish_mutex);
			break ;
		}
		pthread_mutex_unlock(&philo->act->finish_mutex);
		if (ft_now_ms() - start >= sleep)
			break ;
		usleep(1000);
	}
}

int	philo_action(t_philo *philo)
{
	if (handle_single_philo(philo))
		return (1);
	if (take_forks_or_stop(philo))
		return (1);
	if (eat_simulation(philo))
		return (1);
	return (sleep_think_or_stop(philo));
}

void	philo_simulation(t_action *act)
{
	int	i;

	i = 0;
	while (i < act->philo_num)
	{
		if (pthread_create(&act->philos[i].t_id, NULL, thread_action,
				&act->philos[i]) != 0)
		{
			set_finish(act);
			return ;
		}
		i++;
	}
	i = 0;
	monitor_loop(act);
	while (i < act->philo_num)
	{
		pthread_join(act->philos[i].t_id, NULL);
		i++;
	}
}
