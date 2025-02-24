/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:54 by rmakoni           #+#    #+#             */
/*   Updated: 2025/02/24 14:41:05 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	print_action(philo, "has taken a fork");
	print_action(philo, "eating");
	philo->last_eaten = get_time();
	philo->times_eaten = philo->times_eaten + 1;
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
		print_action(philo, "sleeping");
		usleep(philo->data->time_sleep * 1000);
		print_action(philo, "thinking");
	}
	return (NULL);
}
