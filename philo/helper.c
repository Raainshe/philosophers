/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:40:41 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/18 12:48:53 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	t_value;

	gettimeofday(&t_value, NULL);
	return ((t_value.tv_sec * 1000) + (t_value.tv_usec / 1000));
}

void	print_action(t_philo *philo, char *action)
{
	long long	time;
	int			should_print;

	pthread_mutex_lock(&philo->data->death_lock);
	should_print = !philo->data->death;
	pthread_mutex_unlock(&philo->data->death_lock);
	if (should_print)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->no, action);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
}

// Gets the current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Improved version of sleep function
int	ft_usleep(size_t milliseconds, t_data *data)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		pthread_mutex_lock(&data->death_lock);
		if (data->death)
		{
			pthread_mutex_unlock(&data->death_lock);
			return (1);
		}
		pthread_mutex_unlock(&data->death_lock);
		usleep(500);
	}
	return (0);
}
