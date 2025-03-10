/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:44:11 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/10 13:25:47 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long long	time;
	int			result;

	result = 0;
	pthread_mutex_lock(&philo->data->write_lock);
	time = get_time();
	if ((time - philo->data->start_time)
		- philo->last_eaten > philo->data->time_die)
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
		usleep(1000);
	}
	return (NULL);
}
