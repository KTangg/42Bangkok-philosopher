/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spoolpra <spoolpra@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 15:53:19 by spoolpra          #+#    #+#             */
/*   Updated: 2022/03/12 16:33:28 by spoolpra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static long	ft_strict_atoi(char *str)
{
	long	result;

	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (!ft_isdigit(*str))
		{
			printf("Error: Input contain non-digit character\n");
			return (-1);
		}
		result = result * 10;
		result = result + ((*str) - '0');
		str++;
	}
	if (result > 2147483647 || result < 0)
	{
		printf("Error: Input should be positive int type\n");
		return (-1);
	}
	return (result);
}

int	valid_input(int argc, char **argv, t_info *info)
{
	int		i;
	long	input;

	i = -1;
	while (++i < argc)
	{
		input = ft_strict_atoi(argv[i]);
		if (input < 0)
			return (0);
		if (i == 0)
			info->phil_no = input;
		if (i == 1)
			info->die_ms = input;
		if (i == 2)
			info->eat_ms = input;
		if (i == 3)
			info->sleep_ms = input;
		if (i == 4)
			info->times_eat = input;
	}
	if (argc == 4)
		info->times_eat = -1;
	return (1);
}
