/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:57:34 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/13 00:21:22 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct timeval	t_time;

typedef unsigned long	t_timems;

typedef struct s_info
{
	size_t		phil_no;
	size_t		times_eat;
	t_timems	die_ms;
	t_timems	eat_ms;
	t_timems	sleep_ms;
}	t_info;

typedef struct s_fork
{
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
}	t_fork;

typedef struct s_philo
{
	int			alive;
	size_t		no;
	size_t		times_eat;
	t_time		limit;
	t_timems	die_ms;
	t_timems	eat_ms;
	t_timems	sleep_ms;
	t_fork		fork;
}	t_philo;

// Reading Input Process
int				valid_input(int argc, char **argv, t_info *info);

// Initiate Process
int				init_limit(t_philo *philo);
t_philo			*init_philo(t_info *info, pthread_mutex_t *fork_mutex);
pthread_mutex_t	*init_fork(size_t phil_no);

// Simulation Process
void			*routine(void *arg);
int				simulate(t_info *info);

// Time Process
int				timecmp(t_time t1, t_time t2);
t_timems		timems(t_time t);
t_time			add_time(t_time t1, t_timems adding);

// Free Process
void			destroy_mutex(pthread_mutex_t *mutex, size_t phil_no);

#endif
