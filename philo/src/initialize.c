/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:30:11 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 14:24:28 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialize_table(t_table *table, int ac, char **av)
{
	table->philos_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]);
	table->time_to_eat = ft_atol(av[3]);
	table->time_to_sleep = ft_atol(av[4]);
	if (ac == 6)
		table->eat_count = ft_atol(av[5]);
	else
		table->eat_count = -1;
	mutex(table, &table->eating, INIT);
	mutex(table, &table->status, INIT);
	table->all_max_eated = false;
	table->finished = false;
	table->can_start = false;
}

static void	initialize_forks(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->philos_count)
	{
		mutex(table, &table->forks[i], INIT);
		i++;
	}
}

static void	initialize_philos(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->philos_count)
	{
		table->philos[i].id = i;
		table->philos[i].eated_count = 0;
		table->philos[i].last_eat = 0;
		table->philos[i].max_eated = false;
		table->philos[i].right_fork = (i + 1) % table->philos_count;
		table->philos[i].left_fork = i;
		table->philos[i].table = table;
		i++;
	}
}

void	initialize(t_table *table, int ac, char **av)
{
	initialize_table(table, ac, av);
	initialize_forks(table);
	initialize_philos(table);
}
