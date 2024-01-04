/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:52:05 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 14:42:49 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_args(t_table *table, int ac, char **av)
{
	int	i;

	i = 1;
	if (ac != 5 && ac != 6)
	{
		ft_printf("Incorrect format.\n-> ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]");
		free(table);
	}
	if (ft_atol(av[1]) > 32768)
	{
		ft_printf("Too many philosophers. The number max of threads is 32768.");
		free(table);
	}
	while (i < ac)
	{
		if (ft_atol(av[i]) <= 0)
		{
			ft_printf("Argument %d must be positive number.", i);
			free(table);
		}
		i++;
	}
}

void	check(t_table *table, int ac, char **av)
{
	check_args(table, ac, av);
}
