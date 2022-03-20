/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delay.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 12:26:57 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/20 12:57:28 by spoolpra         ###   ########.fr       */
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

t_ms	delay_time(void)
{
	t_time	before;
	t_time	after;
	t_ms	diff;

	gettimeofday(&before, NULL);
	usleep(1000);
	gettimeofday(&after, NULL);
	diff = diff_time(after, before);
	return (diff);
}

int	main(void)
{
	t_ms	diff;

	for (int i = 0; i <= 10; i++)
	{
		diff = delay_time() - 1;
		printf("Sysdelay: %lu ms\n", diff);
	}
}
