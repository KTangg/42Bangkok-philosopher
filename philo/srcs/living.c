/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:41:51 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/17 14:35:36 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_fork(t_philo *philo)
{
	if (philo->left == 1)
	{
		pthread_mutex_unlock(philo->fork.left);
		philo->left = 0;
	}
	if (philo->right == 1)
	{
		pthread_mutex_unlock(philo->fork.right);
		philo->right = 0;
	}
}

void	*pulse_monitor(void *arg)
{
	t_time	now;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		gettimeofday(&now, NULL);
		if (timecmp(now, philo->limit) > 0)
		{
			pthread_mutex_lock(&philo->mutex_alive);
			printf("%08lu %zu died\n", timestamp(philo->start), philo->no);
			philo->alive = 0;
			release_fork(philo);
			pthread_mutex_unlock(&philo->mutex_alive);
		}
	}
	return (NULL);
}

int	alive_check(t_philo *philo)
{
	pthread_t	thread;

	if (pthread_create(&thread, NULL, pulse_monitor, philo) != 0)
	{
		printf("Error: Couldn't create pulse monitor\n");
		return (0);
	}
	if (pthread_detach(thread) != 0)
	{
		printf("Error: Couldn't detach pulse monitor\n");
		return (0);
	}
	return (1);
}

void	*living(void *arg)
{
	t_philo			*philo;
	pthread_mutex_t	mutex_alive;

	philo = (t_philo *)arg;
	pthread_mutex_init(&mutex_alive, NULL);
	philo->mutex_alive = mutex_alive;
	if (!init_limit(philo))
		return (NULL);
	if (!alive_check(philo))
		return (NULL);
	while (philo->alive)
	{
		if (routine(philo))
		{
			pthread_mutex_destroy(&mutex_alive);
			return (NULL);
		}
	}
	pthread_mutex_destroy(&mutex_alive);
	return (NULL);
}
