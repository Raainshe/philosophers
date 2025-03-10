/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:54 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/10 15:58:38 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	if (philo->data->death)
		return ;
	if (philo->data->no_philo == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		print_action(philo, "has taken a fork");
		usleep(philo->data->time_die * 1000 + 1000);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return ;
	}
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->data->write_lock);
	philo->last_eaten = get_time();
	philo->times_eaten = philo->times_eaten + 1;
	pthread_mutex_unlock(&philo->data->write_lock);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->no % 2)
	{
		usleep(15000);
	}
	while (!philo->data->death)
	{
		philo_eating(philo);
		print_action(philo, "is sleeping");
		usleep(philo->data->time_sleep * 1000);
		print_action(philo, "is thinking");
	}
	return (NULL);
}

int	start_simulation(t_data *data)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &routine,
				&data->philos[i]) != 0)
			return (0);
		i++;
	}
	if (pthread_create(&monitor, NULL, &death_monitor, data) != 0)
		return (0);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < data->no_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (1);
}
