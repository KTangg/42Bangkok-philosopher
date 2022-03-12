/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 00:44:39 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/13 01:16:57 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	prepare_eating(t_philo *philo, size_t no, t_fork fork)
{
	t_time	now;

	pthread_mutex_lock(fork.left);
	if (!philo->alive)
	{
		pthread_mutex_unlock(fork.left);
		return (0);
	}
	gettimeofday(&now, NULL);
	printf("%lu %lu has taken a fork\n", timems(now), no);
	pthread_mutex_lock(fork.right);
	if (!philo->alive)
	{
		pthread_mutex_unlock(fork.left);
		pthread_mutex_unlock(fork.right);
		return (0);
	}
	gettimeofday(&now, NULL);
	printf("%lu %lu has taken a fork\n", timems(now), no);
	return (1);
}

int	eating(t_philo *philo, size_t no, t_fork fork)
{
	t_time	now;

	gettimeofday(&now, NULL);
	philo->limit = add_time(now, philo->die_ms);
	printf("%lu %lu is eating\n", timems(now), no);
	usleep(philo->eat_ms * 1000);
	pthread_mutex_unlock(fork.left);
	pthread_mutex_unlock(fork.right);
	return (1);
}

int	complete_eating(t_philo *philo)
{
	if (philo->times_eat > 0)
		philo->times_eat = philo->times_eat - 1;
	if (philo->times_eat == 0)
		return (1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	t_time	now;

	gettimeofday(&now, NULL);
	printf("%lu %lu is sleeping\n", timems(now), philo->no);
	usleep(philo->sleep_ms * 1000);
	gettimeofday(&now, NULL);
	if (philo->alive)
		printf("%lu %lu is thinking\n", timems(now), philo->no);
	return (1);
}

int	routine(t_philo *philo)
{
	if (!prepare_eating(philo, philo->no, philo->fork))
		return (0);
	if (philo->alive)
		eating(philo, philo->no, philo->fork);
	if (philo->alive)
	{
		if (complete_eating(philo))
			return (1);
	}
	if (philo->alive)
		sleeping(philo);
	return (0);
}
