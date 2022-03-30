/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 15:37:29 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/30 17:09:21 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	release_fork(t_philo *philo)
{
	while (philo->fork_cnt != 0)
	{
		sem_post(philo->sem_fork);
		philo->fork_cnt -= 1;
	}
}

void	*pulse_monitor(void *arg)
{
	t_time	now;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive && philo->times_eat != 0)
	{
		gettimeofday(&now, NULL);
		if (timecmp(now, philo->limit) > 0)
		{
			printf("%08lu %zu died\n", timestamp(philo->start), philo->no);
			philo->alive = 0;
			release_fork(philo);
		}
	}
	return (NULL);
}

int	living(t_philo *philo)
{
	if (!prepare_eating(philo))
		return (0);
	if (philo->alive)
		eating(philo);
	if (philo->alive)
	{
		if (complete_eating(philo))
			return (1);
	}
	if (philo->alive)
		sleeping(philo);
	return (0);
}
