/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:44:11 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/10 14:25:36 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_data *data)
{
	int	i;

	i = 0;
	if (data->no_eats == -1)
		return (0);
	while (i < data->no_philo)
	{
		if (data->philos[i].times_eaten < data->no_eats)
			return (0);
		i++;
	}
	i = 0;
	while (i < data->no_philo)
	{
		printf("Philo %d ate %d times ", data->philos[i].no,
				data->philos[i].times_eaten);
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
	if (time_since_last_meal > philo->data->time_die)
	{
		print_action(philo, "died");
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
