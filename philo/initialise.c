/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 13:44:22 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/11 13:47:03 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialise_mutexes(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->no_philo);
	if (!data->forks)
		return (0);
	i = 0;
	while (i < data->no_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->write_lock, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->death_lock, NULL) != 0)
		return (0);
	return (1);
}

void	initialise_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->no_philo)
	{
		data->philos[i].no = i + 1;
		data->philos[i].data = data;
		data->philos[i].last_eaten = data->start_time;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % data->no_philo;
		if (data->no_philo == 1)
		{
			data->philos[i].left_fork = 0;
			data->philos[i].right_fork = 0;
		}
		data->philos[i].times_eaten = 0;
		i++;
	}
}

int	initialise_time_and_philo(t_data *data)
{
	struct timeval	t_value;

	gettimeofday(&t_value, NULL);
	data->start_time = (t_value.tv_sec * 1000) + t_value.tv_usec / 1000;
	data->philos = malloc(sizeof(t_philo) * data->no_philo);
	if (!data->philos)
		return (0);
	initialise_philo(data);
	return (1);
}

t_data	*initialise_params(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->no_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	data->no_eats = -1;
	if (argc == 6)
		data->no_eats = ft_atoi(argv[5]);
	data->death = false;
	if (!initialise_time_and_philo(data))
		return (free(data), NULL);
	if (!initialise_mutexes(data))
		return (clean_up(data), NULL);
	return (data);
}
