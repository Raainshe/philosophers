/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 14:21:59 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/11 14:25:58 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialise_fork_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->no_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			data->initialised_mutexes = i;
			return (0);
		}
		i++;
	}
	data->initialised_mutexes = data->no_philo;
	return (1);
}

int	initialise_control_mutexes(t_data *data)
{
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
	{
		data->write_lock_initialised = false;
		return (0);
	}
	data->write_lock_initialised = true;

	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
	{
		data->death_lock_initialised = false;
		return (0);
	}
	data->death_lock_initialised = true;
	return (1);
}