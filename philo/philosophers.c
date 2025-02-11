/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:06:34 by rmakoni           #+#    #+#             */
/*   Updated: 2025/02/11 16:15:16 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	initialise(int argc, char **argv)
{
	t_philo	*philo;
	int		no_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;

	*philo = malloc(ft_atoi(argv[])
}

int	main(int argc, char **argv)
{
	if (check_params(argc, argv) == 0)
		return (error_msg(), 1);
}
