/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 14:57:18 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/27 13:39:55 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_usage(int argc)
{
	char	*s0;
	char	*s1;
	char	*s2;

	if (argc != 5 && argc != 6)
	{
		s0 = "Usage:";
		s1 = "./philo {number_of_philosophers} {time_to_die} {time_to_eat}";
		s2 = "{time_to_sleep} [number_of_times_each_philosopher_must_eat]";
		printf("%s %s %s\n", s0, s1, s2);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (!valid_usage(argc))
		return (1);
	if (!valid_input(argc - 1, argv + 1, &info))
		return (2);
	if (!simulate(&info))
		return (3);
	return (0);
}
