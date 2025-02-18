/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:11:15 by rmakoni           #+#    #+#             */
/*   Updated: 2025/02/18 14:25:22 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int num)
{
	if (num >= '0' && num <= '9')
		return (1);
	else
		return (0);
}

void	error_msg(void)
{
	printf("You have entered the incorrect perameters! Please enter:\n");
	printf("./philo {number_of_philosopher {time_to_die} {time_to_eat}\n");
	printf("{time_to_sleep} [number_of_times_each_philosopher_must_eat]\n");
}

//returns 1 if params are correct and 0 if not
int	check_params(int argc, char **argv)
{
	int	i;
	int	x;

	i = 1;
	if (argc == 5 || argc == 6)
	{
		while (i <= argc - 1)
		{
			x = 0;
			while (argv[i][x] != '\0')
			{
				if (!ft_isdigit(argv[i][x]))
					return (0);
				x++;
			}
			i++;
		}
	}
	else
		return (0);
	return (1);
}
