/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 00:44:39 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/17 14:27:21 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	prepare_eating(t_philo *philo, size_t no, t_fork fork)
{
	pthread_mutex_lock(fork.left);
	philo->left = 1;
	if (!philo->alive)
	{
		release_fork(philo);
		return (0);
	}
	printf("%08lu %lu has taken a fork\n", timestamp(philo->start), no);
	pthread_mutex_lock(fork.right);
	philo->right = 1;
	if (!philo->alive)
	{
		release_fork(philo);
		return (0);
	}
	printf("%08lu %lu has taken a fork\n", timestamp(philo->start), no);
	return (1);
}

int	eating(t_philo *philo, size_t no, t_fork fork)
{
	t_time	now;

	gettimeofday(&now, NULL);
	philo->limit = add_time(now, philo->die_ms);
	printf("%08lu %lu is eating\n", timestamp(philo->start), no);
	usleep(philo->eat_ms * 1000);
	pthread_mutex_unlock(fork.left);
	philo->left = 0;
	pthread_mutex_unlock(fork.right);
	philo->right = 0;
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
	printf("%08lu %lu is sleeping\n", timestamp(philo->start), philo->no);
	usleep(philo->sleep_ms * 1000);
	pthread_mutex_unlock(&philo->mutex_alive);
	usleep(10);
	pthread_mutex_lock(&philo->mutex_alive);
	if (philo->alive)
		printf("%08lu %lu is thinking\n", timestamp(philo->start), philo->no);
	pthread_mutex_unlock(&philo->mutex_alive);
	return (1);
}

int	routine(t_philo *philo)
{
	if (!prepare_eating(philo, philo->no, philo->fork))
		return (0);
	pthread_mutex_lock(&philo->mutex_alive);
	if (philo->alive)
		eating(philo, philo->no, philo->fork);
	pthread_mutex_unlock(&philo->mutex_alive);
	usleep(10);
	pthread_mutex_lock(&philo->mutex_alive);
	if (philo->alive)
	{
		if (complete_eating(philo))
			return (1);
	}
	pthread_mutex_unlock(&philo->mutex_alive);
	usleep(10);
	pthread_mutex_lock(&philo->mutex_alive);
	if (philo->alive)
		sleeping(philo);
	pthread_mutex_unlock(&philo->mutex_alive);
	return (0);
}
