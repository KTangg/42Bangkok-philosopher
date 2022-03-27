/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 21:30:38 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/17 14:27:27 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_time	add_time(t_time t1, t_timems adding)
{
	size_t	sec;
	size_t	usec;
	size_t	buff;
	t_time	result;

	sec = adding / 1000;
	result.tv_sec = t1.tv_sec + sec;
	usec = (adding % 1000) * 1000;
	buff = usec + t1.tv_usec;
	result.tv_sec = result.tv_sec + (buff / 1000000);
	result.tv_usec = buff % 1000000;
	return (result);
}

t_timems	timems(t_time t)
{
	t_timems	result;

	result = t.tv_sec * 1000;
	result = result + (t.tv_usec / 1000);
	return (result);
}

int	timecmp(t_time t1, t_time t2)
{
	if (t1.tv_sec > t2.tv_sec)
		return (1);
	else if (t1.tv_sec < t2.tv_sec)
		return (-1);
	else
	{
		if (t1.tv_usec > t2.tv_usec)
			return (1);
		else if (t1.tv_usec < t2.tv_usec)
			return (-1);
		else
			return (0);
	}
}

long	timestamp(t_time start)
{
	long	result;
	t_time	now;

	gettimeofday(&now, NULL);
	result = timems(now) - timems(start);
	return (result);
}
