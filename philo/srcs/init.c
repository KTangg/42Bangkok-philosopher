/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:45:00 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/17 14:38:20 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_limit(t_philo *philo)
{
	t_time	current;

	if (gettimeofday(&current, NULL) != 0)
	{
		printf("Error: Entounter error while getting current time\n");
		return (0);
	}
	philo->limit = add_time(current, philo->die_ms);
	philo->right = 0;
	philo->left = 0;
	return (1);
}

pthread_mutex_t	*init_fork(size_t phil_no)
{
	size_t			i;
	pthread_mutex_t	*fork_mutex;

	fork_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * phil_no);
	if (!fork_mutex)
	{
		printf("Error: Allocate memory for fork failed\n");
		return (NULL);
	}
	i = 0;
	while (i < phil_no)
	{
		if (pthread_mutex_init(&fork_mutex[i++], NULL) != 0)
		{
			printf("Error: Encounter error while init fork\n");
			free(fork_mutex);
			return (NULL);
		}
	}
	return (fork_mutex);
}

t_fork	assign_fork(size_t i, pthread_mutex_t *fork_mutex, size_t phil_no)
{
	t_fork	fork;

	if (i == 0)
		fork.left = &fork_mutex[phil_no - 1];
	else
		fork.left = &fork_mutex[i - 1];
	fork.right = &fork_mutex[i];
	return (fork);
}

t_philo	*init_philo(t_info *info, pthread_mutex_t *fork_mutex)
{
	int		i;
	size_t	phil_no;
	t_fork	fork;
	t_philo	*philo;

	phil_no = info->phil_no;
	philo = (t_philo *)malloc(sizeof(t_philo) * phil_no);
	if (!philo)
	{
		printf("Error: Allocate memory for philos failed\n");
		return (NULL);
	}
	i = -1;
	while (++i < (int)phil_no)
	{
		philo[i].alive = 1;
		philo[i].no = i + 1;
		philo[i].times_eat = info->times_eat;
		philo[i].die_ms = info->die_ms;
		philo[i].eat_ms = info->eat_ms;
		philo[i].sleep_ms = info->sleep_ms;
		fork = assign_fork(i, fork_mutex, phil_no);
		philo[i].fork = fork;
	}
	return (philo);
}

int	init_start(t_philo *philo, size_t philo_no)
{
	int		i;
	t_time	current;

	gettimeofday(&current, NULL);
	i = 0;
	while (i < (int)philo_no)
	{
		philo[i].start = current;
		i++;
	}
	return (1);
}
