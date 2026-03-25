/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 20:33:04 by inhlee            #+#    #+#             */
/*   Updated: 2026/01/29 18:55:25 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	main(int argc, char **argv)
{
	t_action	act;

	if (!(argc == 6 || argc == 5))
		return (1);
	if (init_action(&act, argv, argc) != 0)
		return (1);
	if (init_mutex(&act) != 0)
		return (1);
	if (init_philos(&act) != 0)
		return (1);
	philo_simulation(&act);
	pthread_destroy_all(&act);
	return (0);
}
