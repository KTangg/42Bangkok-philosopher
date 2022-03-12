/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 19:34:21 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/12 19:44:05 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(pthread_mutex_t *mutex, size_t phil_no)
{
	size_t	i;

	i = 0;
	while (i < phil_no)
	{
		pthread_mutex_destroy(&mutex[i]);
		i++;
	}
	free(mutex);
	mutex = NULL;
}
