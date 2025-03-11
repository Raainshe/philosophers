/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:28:54 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/11 16:33:49 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating_two(t_philo *philo, int first_fork, int second_fork)
{
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	print_action(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	print_action(philo, "has taken a fork");
	print_action(philo, "is eating");
	pthread_mutex_lock(&philo->state_lock);
	philo->last_eaten = get_time();
	philo->times_eaten = philo->times_eaten + 1;
	pthread_mutex_unlock(&philo->state_lock);
	usleep(philo->data->time_eat * 1000);
	pthread_mutex_unlock(&philo->data->forks[second_fork]);
	pthread_mutex_unlock(&philo->data->forks[first_fork]);
}

void	philo_eating(t_philo *philo)
{
	int	first_fork;
	int	second_fork;

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
	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (second_fork < first_fork)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	philo_eating_two(philo, first_fork, second_fork);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		death_status;

	philo = (t_philo *)arg;
	if (philo->no % 2)
	{
		usleep(15000);
	}
	pthread_mutex_lock(&philo->state_lock);
	philo->last_eaten = get_time();
	pthread_mutex_unlock(&philo->state_lock);
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_lock);
		death_status = philo->data->death;
		pthread_mutex_unlock(&philo->data->death_lock);
		if (death_status)
			break ;
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
