/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   living.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:41:51 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/13 00:44:05 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*pulse_monitor(void *arg)
{
	t_time	now;
	t_time	limit;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (philo->alive)
	{
		limit = philo->limit;
		if (gettimeofday(&now, NULL) != 0)
		{
			printf("Error: Couldn't get current time\n");
			return (NULL);
		}
		if (timecmp(now, limit) > 0)
		{
			printf("%lu %zu died\n", timems(now), philo->no);
			philo->alive = 0;
		}
	}
	return (NULL);
}

int		alive_check(t_philo *philo)
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
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!init_limit(philo))
		return (NULL);
	printf("Limit philo %zu at %lu sec %d usec\n", philo->no, philo->limit.tv_sec, philo->limit.tv_usec);
	if (!alive_check(philo))
		return (NULL);
	while (philo->alive)
		routine(philo);
	return (NULL);
}
