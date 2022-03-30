/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 18:45:00 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/30 15:31:11 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	init_philo(int no, t_info *info)
{
	t_philo	philo;

	philo.alive = 1;
	philo.forks = 0;
	philo.no = no;
	philo.times_eat = info->times_eat;
	philo.die_ms = info->die_ms;
	philo.eat_ms = info->eat_ms;
	philo.sleep_ms = info->sleep_ms;
	gettimeofday(&philo.start, NULL);
	philo.limit = add_time(philo.start, philo.die_ms);
	return (philo);
}
