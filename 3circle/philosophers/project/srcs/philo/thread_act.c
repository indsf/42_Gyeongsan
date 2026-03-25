/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_act.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 14:28:09 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/30 19:09:42 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*thread_action(void *argv)
{
	t_philo		*philo;
	t_action	*act;

	philo = (t_philo *)argv;
	act = philo->act;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!ft_check(philo))
	{
		if (philo_action(philo))
			break ;
	}
	return (NULL);
}

int	ft_die_check(t_action *act, long long now)
{
	int			i;
	long long	last;

	i = 0;
	while (i < act->philo_num)
	{
		pthread_mutex_lock(&act->meal_mutex);
		last = act->philos[i].last_eat;
		pthread_mutex_unlock(&act->meal_mutex);
		if (now - last >= act->die)
		{
			die_check_printf(act, act->philos[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_monitor_finish(t_action *act)
{
	int	done;

	if (&act->meal_mutex <= 0)
		return (0);
	pthread_mutex_lock(&act->meal_mutex);
	done = (act->finished_eat >= act->philo_num);
	pthread_mutex_unlock(&act->meal_mutex);
	if (done)
	{
		set_finish(act);
		return (1);
	}
	return (0);
}

void	monitor_loop(t_action *act)
{
	long long	now;

	while (!ft_finish(act))
	{
		now = ft_now_ms();
		if (ft_die_check(act, now))
			return ;
		if (check_monitor_finish(act))
			return ;
		usleep(200);
	}
}
