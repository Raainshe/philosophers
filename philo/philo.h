/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmakoni <rmakoni@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 13:06:37 by rmakoni           #+#    #+#             */
/*   Updated: 2025/03/17 18:15:48 by rmakoni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				no;
	int				times_eaten;
	int				right_fork;
	int				left_fork;
	long long		last_eaten;
	pthread_t		thread;
	pthread_mutex_t	state_lock;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				no_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				no_eats;
	bool			death;
	long long		start_time;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	int				initialised_mutexes;
	bool			write_lock_initialised;
	bool			death_lock_initialised;
}					t_data;

int					check_params(int argc, char **argv);
void				error_msg(void);
int					ft_atoi(const char *str);
t_data				*initialise_params(int argc, char **argv);
void				print_action(t_philo *philo, char *action);
long long			get_time(void);
void				*death_monitor(void *arg);
int					start_simulation(t_data *data);
void				clean_up(t_data *data);
int					initialise_fork_mutexes(t_data *data);
int					initialise_control_mutexes(t_data *data);
int					ft_usleep(size_t milliseconds, t_data *data);
#endif