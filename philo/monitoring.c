/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:44:11 by rmakoni           #+#    #+#             */
/*   Updated: 2025/02/25 14:01:15 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo *philo)
{
	long long	time;

	time = get_time();
	if (time - philo->last_eaten > philo->data->time_die)
	{
		print_action(philo, "Died");
		philo->data->death = true;
		return (1);
	}
	return (0);
}

void	*death_monitor(void *arg)
{
	t_data	*data;
	int		i;
	bool	everyone_eaten;

	data = (t_data *)arg;
	while (!data->death)
	{
		i = 0;
		everyone_eaten = true;
		while (i < data->no_philo)
		{
			if (is_dead(&data->philos[i]))
				return (NULL);
			if (data->no_eats != -1
				&& data->philos[i].times_eaten < data->no_eats)
				everyone_eaten = false;
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
