/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:23:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/17 14:36:30 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	create_thread(t_philo *philo, size_t philo_no, pthread_t *thread)
{
	size_t	i;

	i = 0;
	while (i < philo_no)
	{
		if (pthread_create(&thread[i], NULL, living, &philo[i]) != 0)
			return (0);
		usleep(50);
		i++;
	}
	return (1);
}

int	join_thread(size_t phil_no, pthread_t *thread)
{
	size_t	i;

	i = 0;
	while (i < phil_no)
	{
		if (pthread_join(thread[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

int	run_simulator(t_philo *philo, size_t philo_no)
{
	pthread_t	*thread;

	thread = (pthread_t *)malloc(sizeof(thread) * philo_no);
	if (!thread)
	{
		printf("Error: Allocate memory for threads failed\n");
		return (0);
	}
	if (!create_thread(philo, philo_no, thread))
	{
		printf("Error: Thread create failed\n");
		free(thread);
		return (0);
	}
	if (!join_thread(philo_no, thread))
	{
		printf("Error: Thread join failed\n");
		free(thread);
		return (0);
	}
	free(thread);
	return (1);
}

int	simulate(t_info *info)
{
	t_philo			*philo;
	pthread_mutex_t	*fork_mutex;

	fork_mutex = init_fork(info->phil_no);
	if (!fork_mutex)
		return (0);
	philo = init_philo(info, fork_mutex);
	init_start(philo, info->phil_no);
	if (!philo)
	{
		destroy_mutex(fork_mutex, info->phil_no);
		return (0);
	}
	if (!run_simulator(philo, info->phil_no))
	{
		destroy_mutex(fork_mutex, info->phil_no);
		free(philo);
		return (0);
	}
	destroy_mutex(fork_mutex, info->phil_no);
	free(philo);
	return (1);
}
