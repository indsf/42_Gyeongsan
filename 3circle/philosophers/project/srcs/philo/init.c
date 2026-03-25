/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:44:21 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/30 13:13:52 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	init_action(t_action *act, char **argv, int argc)
{
	act->philo_num = ft_atoi(argv[1]);
	act->die = ft_atoi(argv[2]);
	act->eat = ft_atoi(argv[3]);
	act->sleep = ft_atoi(argv[4]);
	if (act->philo_num <= 0 || act->die <= 0
		|| act->eat <= 0 || act->sleep <= 0)
		return (1);
	if (argc == 6)
	{
		act->must_eat = ft_atoi(argv[5]);
		if (act->must_eat <= 0)
			return (1);
	}
	else
		act->must_eat = 0;
	return (0);
}

int	init_mutex(t_action *act)
{
	int	i;

	i = 0;
	act->forks = malloc(sizeof(pthread_mutex_t) * act->philo_num);
	if (!act->forks)
		return (1);
	if (pthread_mutex_init(&act->write_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&act->meal_mutex, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&act->finish_mutex, NULL) != 0)
		return (1);
	act->finished_eat = 0;
	act->finish = RUNNING;
	act->start_ms = ft_now_ms();
	while (i < act->philo_num)
	{
		if (pthread_mutex_init(&act->forks[i], NULL) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_philos(t_action *act)
{
	int	i;

	i = 0;
	act->philos = malloc(sizeof(t_philo) * act->philo_num);
	if (!act->philos)
		return (1);
	while (i < act->philo_num)
	{
		act->philos[i].id = i + 1;
		act->philos[i].left_fork = &act->forks[i];
		act->philos[i].right_fork = &act->forks[(i + 1) % act->philo_num];
		act->philos[i].meal_mutex = &act->meal_mutex;
		act->philos[i].write_mutex = &act->write_mutex;
		act->philos[i].full = 0;
		act->philos[i].eat_ct = 0;
		act->philos[i].last_eat = act->start_ms;
		act->philos[i].act = act;
		i++;
	}
	return (0);
}
