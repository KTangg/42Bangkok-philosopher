/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:26:57 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/30 16:30:35 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct timeval	t_time;
typedef unsigned long	t_ms;

t_ms	diff_time(t_time t1, t_time t2)
{
	t_ms	t1_ms;
	t_ms	t2_ms;
	t_ms	diff;

	t1_ms = (t1.tv_sec * 1000) + (t1.tv_usec / 1000);
	t2_ms = (t2.tv_sec * 1000) + (t2.tv_usec / 1000);
	diff = t1_ms - t2_ms;
	return (diff);
}

t_ms	delay_time(int sleep_ms)
{
	t_time	before;
	t_time	after;
	t_ms	diff;

	gettimeofday(&before, NULL);
	usleep(sleep_ms * 1000);
	gettimeofday(&after, NULL);
	diff = diff_time(after, before) - sleep_ms;
	return (diff);
}

int	main(void)
{
	int		count;
	int		sleep_ms;
	t_ms	diff;
	t_ms	total;
	double	avg;

	count = 0;
	total = 0;
	sleep_ms = 100;
	while (count++ < 20)
	{
		diff = delay_time(sleep_ms);
		printf("Sysdelay: %lu ms\n", diff);
		total = total + diff;
	}
	avg = (double)total / count;
	printf ("Average Sysdelay: %f ms\n", avg);
}
