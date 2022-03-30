/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:07:39 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/30 16:26:54 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

int	prepare_eating(t_philo *philo)
{
	sem_wait(philo->sem_fork);
	philo->fork_cnt += 1;
	if (!philo->alive)
	{
		release_fork(philo);
		return (0);
	}
	printf("%08lu %zu has taken a fork\n", timestamp(philo->start), philo->no);
	sem_wait(philo->sem_fork);
	philo->fork_cnt += 1;
	if (!philo->alive)
	{
		release_fork(philo);
		return (0);
	}
	printf("%08lu %zu has taken a fork\n", timestamp(philo->start), philo->no);
	return (1);
}

int	eating(t_philo *philo)
{
	t_time	now;

	gettimeofday(&now, NULL);
	philo->limit = add_time(now, philo->die_ms);
	printf("%08lu %lu is eating\n", timestamp(philo->start), philo->no);
	usleep(philo->eat_ms * 1000);
	release_fork(philo);
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
	if (philo->alive)
		printf("%08lu %lu is thinking\n", timestamp(philo->start), philo->no);
	return (1);
}
