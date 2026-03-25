/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:04:23 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/30 13:10:34 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stddef.h>
# include <sys/time.h>

# define PHILO_MAX_COUNT 200

typedef enum e_stop_check
{
	RUNNING = 0,
	FINISHED = 1
}					t_stop_check;

typedef struct s_philo
{
	int				id;
	int				full;
	int				eat_ct;
	long long		last_eat;
	pthread_t		t_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*meal_mutex;
	struct s_action	*act;
}					t_philo;

typedef struct s_action
{
	int				philo_num;
	int				die;
	int				eat;
	int				sleep;
	int				must_eat;
	long long		start_ms;
	int				finished_eat;
	t_stop_check	finish;
	pthread_mutex_t	finish_mutex;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	meal_mutex;
}					t_action;

void				philo_simulation(t_action *act);
int					philo_action(t_philo *philo);
void				*thread_action(void *argv);
int					ft_die_check(t_action *act, long long now);
int					check_monitor_finish(t_action *act);
void				monitor_loop(t_action *act);
#endif