/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:57:34 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/30 16:21:38 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>

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

typedef struct s_philo
{
	int				alive;
	size_t			fork_cnt;
	size_t			no;
	size_t			times_eat;
	t_time			start;
	t_time			limit;
	t_timems		die_ms;
	t_timems		eat_ms;
	t_timems		sleep_ms;
	sem_t			*sem_fork;
}	t_philo;

// Reading Input Process
int				valid_input(int argc, char **argv, t_info *info);

// Simulation Process
void			*pulse_monitor(void *arg);
void			release_fork(t_philo *philo);
int				living(t_philo *philo);
int				simulate(t_info *info);

// Routine Process
int				prepare_eating(t_philo *philo);
int				eating(t_philo *philo);
int				complete_eating(t_philo *philo);
int				sleeping(t_philo *philo);

// Initiate Process
t_philo			init_philo(int no, t_info *info, sem_t *sem_fork);

// Time Process
int				timecmp(t_time t1, t_time t2);
long			timestamp(t_time start);
t_timems		timems(t_time t);
t_time			add_time(t_time t1, t_timems adding);

#endif
