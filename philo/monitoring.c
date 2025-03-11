/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:44:11 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/11 13:06:36 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_data *data)
{
	int	i;
	int	eaten_count;

	i = 0;
	if (data->no_eats == -1)
		return (0);
	while (i < data->no_philo)
	{
		pthread_mutex_lock(&data->write_lock);
		eaten_count = data->philos[i].times_eaten;
		pthread_mutex_unlock(&data->write_lock);
		if (eaten_count < data->no_eats)
			return (0);
		i++;
	}
	return (1);
}

int	is_dead(t_philo *philo)
{
	long long	time_since_last_meal;
	int			result;

	result = 0;
	pthread_mutex_lock(&philo->data->write_lock);
	time_since_last_meal = get_time() - philo->last_eaten;
	if (time_since_last_meal > philo->data->time_die && !philo->data->death)
	{
		printf("%lld %d has died\n", get_time() - philo->data->start_time);
		printf("%d has died\n", philo->no);
		philo->data->death = true;
		result = 1;
	}
	pthread_mutex_unlock(&philo->data->write_lock);
	return (result);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (!data->death)
	{
		i = 0;
		while (i < data->no_philo)
		{
			if (is_dead(&data->philos[i]))
				return (NULL);
			i++;
		}
		if (all_eaten(data))
		{
			pthread_mutex_lock(&data->write_lock);
			data->death = true;
			pthread_mutex_unlock(&data->write_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
