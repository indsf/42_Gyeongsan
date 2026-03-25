/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 22:01:58 by inhlee            #+#    #+#             */
/*   Updated: 2025/12/22 16:55:40 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "philo.h"

int	init_action(t_action *act, char **argv, int argc);
int	init_philos(t_action *act);
int	init_mutex(t_action *act);

#endif