/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:23:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/30 16:20:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/wait.h>

int	create_philo(int no, t_info *info, sem_t *forks)
{
	t_philo		philo;
	pthread_t	pulse_thread;

	philo = init_philo(no, info, forks);
	if (pthread_create(&pulse_thread, NULL, pulse_monitor, &philo) != 0)
	{
		printf("Error: Couldn't Create Pulse Thread on Philo %d", no);
		return (0);
	}
	while (philo.alive)
		living(&philo);
	if (pthread_join(pulse_thread, NULL) != 0)
	{
		printf("Error: Couldn't Join Pulse Thread on Philo %d", no);
		return (0);
	}
	return (1);
}

int	wait_philo(pid_t *philo_pid, size_t phil_no)
{
	size_t	i;

	i = 0;
	while (i < phil_no)
		waitpid(philo_pid[i++], NULL, 0);
	return (1);
}

int	create_process(t_info *info, sem_t *forks)
{
	int		i;
	pid_t	pid;
	pid_t	*philo_pid;

	philo_pid = (pid_t *)malloc(sizeof(pid_t) * info->phil_no);
	if (!philo_pid)
		exit(1);
	pid = 1;
	i = -1;
	while (++i < (int)(info->phil_no) && pid != 0)
	{
		if (pid != 0)
		{
			usleep(50);
			pid = fork();
			if (pid == 0)
				create_philo(i, info, forks);
			if (pid != 0)
				philo_pid[i] = pid;
		}
	}
	if (pid != 0)
		wait_philo(philo_pid, info->phil_no);
	free(philo_pid);
	return (1);
}

int	simulate(t_info *info)
{
	sem_t	*sem_fork;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fail to Create Child Process\n");
		return (0);
	}
	if (pid == 0)
	{
		sem_fork = sem_open("sem_fork", O_CREAT,
				S_IRUSR | S_IWUSR, info->phil_no);
		create_process(info, sem_fork);
		sem_close(sem_fork);
		sem_unlink("sem_fork");
	}
	else
		waitpid(pid, NULL, 0);
	return (1);
}
