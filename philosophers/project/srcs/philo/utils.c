/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 21:04:50 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/30 19:10:59 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_atoi(const char *nptr)
{
	int			i;
	int			j;
	long long	result;

	i = 0;
	result = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	j = i - 1;
	while (nptr[++j])
	{
		if (!(nptr[j] >= 48 && nptr[j] <= 57))
			return (-1);
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		result = (nptr[i] - 48) + result * 10;
		if (result > 2147483647)
			return (-1);
		i++;
	}
	return (result);
}

void	pthread_destroy_all(t_action *action)
{
	int	i;

	i = 0;
	if (action->forks)
	{
		while (i < action->philo_num)
		{
			pthread_mutex_destroy(&action->forks[i]);
			i++;
		}
	}
	pthread_mutex_destroy(&action->write_mutex);
	pthread_mutex_destroy(&action->meal_mutex);
	pthread_mutex_destroy(&action->finish_mutex);
	free(action->forks);
	action->forks = NULL;
	free(action->philos);
	action->philos = NULL;
}

long long	ft_now_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) == -1)
		return (-1);
	return ((tv.tv_sec * 1000LL) + (tv.tv_usec / 1000));
}

int	ft_check(t_philo *philo)
{
	int	ret;

	pthread_mutex_lock(&philo->act->finish_mutex);
	if (philo->act->finish == FINISHED)
		ret = 1;
	else
		ret = 0;
	pthread_mutex_unlock(&philo->act->finish_mutex);
	return (ret);
}
