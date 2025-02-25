/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 14:06:34 by rmakoni           #+#    #+#             */
/*   Updated: 2025/02/25 13:05:44 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	*data;

	if (check_params(argc, argv) == 0)
		return (error_msg(), 1);
	data = initialise_params(argc, argv);
	if (!data)
		return (1);
	if (start_simulation(data) == 0)
		return (clean_up(data), 1);
}
