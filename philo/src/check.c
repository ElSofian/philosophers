/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:52:05 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 13:30:20 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_nums(int ac, char **av)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_nbrlength(ft_atol(av[i])) > 10)
		{
			ft_printf("Argument %d has to fit in an int.\n", i);
			exit(EXIT_FAILURE);
		}
		if (ft_atol(av[i]) <= 0)
		{
			ft_printf("Argument %d must be positive number.\n", i);
			exit(EXIT_FAILURE);
		}
		if ((i == 2 || i == 3 || i == 4) && ft_atol(av[i]) < 0)
		{
			ft_printf("Argument %d must be greater than 0ms.\n", i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

static void	check_args(int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		ft_printf("Incorrect format.\n-> ./philo number_of_philosophers time_to_die \
time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		exit(EXIT_FAILURE);
	}
	if (ft_atol(av[1]) < 2 || ft_atol(av[1]) > 200)
	{
		ft_printf("Too many or not enough philosophers.\n");
		exit(EXIT_FAILURE);
	}
}

void	check(int ac, char **av)
{
	check_args(ac, av);
	check_nums(ac, av);
}
