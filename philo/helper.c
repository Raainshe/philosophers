/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 14:40:41 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/11 13:04:42 by rmakoni          ###   ########.fr       */
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

	pthread_mutex_lock(&philo->data->write_lock);
	if (!philo->data->death)
	{
		time = get_time() - philo->data->start_time;
		printf("%lld %d %s\n", time, philo->no, action);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
}
