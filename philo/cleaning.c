/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 13:23:44 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/11 14:47:53 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_up_state(t_data *data)
{
	int	i;

	i = 0;
	if (data->philos)
	{
		while (i < data->no_philo)
		{
			pthread_mutex_destroy(&data->philos[i].state_lock);
			i++;
		}
	}
}

void	clean_up(t_data *data)
{
	int	i;

	if (data)
	{
		if (data->forks)
		{
			i = 0;
			while (i < data->initialised_mutexes)
			{
				pthread_mutex_destroy(&data->forks[i]);
				i++;
			}
			free(data->forks);
		}
		clean_up_state(data);
		if (data->write_lock_initialised)
			pthread_mutex_destroy(&data->write_lock);
		if (data->death_lock_initialised)
			pthread_mutex_destroy(&data->death_lock);
		if (data->philos)
			free(data->philos);
		free(data);
	}
}
