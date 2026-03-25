/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:06:43 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/30 19:15:52 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	philo_printf(t_philo *philo, const char *str)
{
	long long	now;

	pthread_mutex_lock(philo->write_mutex);
	pthread_mutex_lock(&philo->act->finish_mutex);
	now = ft_now_ms();
	if (now < 0)
		return (1);
	if (philo->act->finish == RUNNING)
		printf("%lld %d %s", now - philo->act->start_ms, philo->id, str);
	pthread_mutex_unlock(&philo->act->finish_mutex);
	pthread_mutex_unlock(philo->write_mutex);
	return (0);
}

void	die_check_printf(t_action *act, int p_id)
{
	long long	now;

	pthread_mutex_lock(&act->write_mutex);
	pthread_mutex_lock(&act->finish_mutex);
	if (act->finish == RUNNING)
	{
		now = ft_now_ms();
		if (now < 0)
			return ;
		printf("%lld %d died\n", now - act->start_ms, p_id);
		act->finish = FINISHED;
	}
	pthread_mutex_unlock(&act->finish_mutex);
	pthread_mutex_unlock(&act->write_mutex);
}

void	set_finish(t_action *act)
{
	pthread_mutex_lock(&act->finish_mutex);
	act->finish = FINISHED;
	pthread_mutex_unlock(&act->finish_mutex);
}

int	ft_finish(t_action *act)
{
	int	ret;

	pthread_mutex_lock(&act->finish_mutex);
	ret = (act->finish == FINISHED);
	pthread_mutex_unlock(&act->finish_mutex);
	return (ret);
}
