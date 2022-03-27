/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:23:40 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/27 22:12:45 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <sys/wait.h>

int	create_philo(int no, t_info *info)
{
	t_philo	philo;

	philo = init_philo(no, info);
	printf("philo %lu die %lu\n", philo.no, philo.die_ms);
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

int	create_process(t_info *info)
{
	pid_t	pid;
	pid_t	*philo_pid;
	size_t	i;

	philo_pid = (pid_t *)malloc(sizeof(pid_t) * info->phil_no);
	if (!philo_pid)
		exit(1);
	pid = 1;
	i = 0;
	while (i < info->phil_no)
	{
		if (pid != 0)
		{
			pid = fork();
			if (pid == 0)
				create_philo(i, info);
			if (pid != 0)
				philo_pid[i] = pid;
		}
		i++;
	}
	if (pid != 0)
		wait_philo(philo_pid, info->phil_no);
	free(philo_pid);
	return (1);
}

int	simulate(t_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		printf("Fail to Create Child Process\n");
		return (0);
	}
	if (pid == 0)
		create_process(info);
	else
		waitpid(pid, NULL, 0);
	return (1);
}
