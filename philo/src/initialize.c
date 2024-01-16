/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:30:11 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 17:59:53 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialize_table(t_table *table, int ac, char **av)
{
	table->philos_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1000;
	table->time_to_eat = ft_atol(av[3]) * 1000;
	table->time_to_sleep = ft_atol(av[4]) * 1000;
	table->can_start = false;
	if (ac == 6)
		table->eat_count = ft_atol(av[5]);
	else
		table->eat_count = -1;
	table->fork = (t_fork *)malloc(sizeof(t_fork) * table->philos_count);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->philos_count);
	table->threads = 0;
	table->finished = false;
	table->can_start = false;
	mutex(&table->mutex, INIT);
	mutex(&table->status, INIT);
}

static void	initialize_forks(t_table *table)
{
	long	i;
	t_fork	*fork;

	i = 0;
	while (i < table->philos_count)
	{
		fork = table->fork + i;
		fork->id = i + 1;
		fork->using = false;
		mutex(&fork->mutex, INIT);
		fork->table = table;
		i++;
	}
}

static void	initialize_philos(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = 0;
	while (i < table->philos_count)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->eated_count = 0;
		philo->max_eated = false;
		mutex(&philo->mutex, INIT);
		philo->table = table;
		if (philo->id % 2 == 0)
		{
			philo->right_fork = &table->fork[i];
			philo->left_fork = &table->fork[(i + 1) % table->philos_count];
		}
		else
		{
			philo->right_fork = &table->fork[(i + 1) % table->philos_count];
			philo->left_fork = &table->fork[i];
		}
		i++;
	}
}

static void	initialize_dinner(t_table *table)
{
	int	i;

	if (table->eat_count == 0)
		return ;
	i = 0;
	while (i < table->philos_count)
	{
		thread(&table->philo[i].thread, dinner, &table->philo[i], CREATE);
		i++;
	}
	thread(&table->searcher, search, table, CREATE);
	table->start_time = get_time(MILLISECONDS);
	set_bool(&table->mutex, &table->can_start, true);
	i = 0;
	while (i < table->philos_count)
	{
		thread(&table->philo[i].thread, NULL, NULL, JOIN);
		i++;
	}
	set_bool(&table->mutex, &table->finished, true);
	thread(&table->searcher, NULL, NULL, JOIN);
}

void	initialize(t_table *table, int ac, char **av)
{
	initialize_table(table, ac, av);
	initialize_forks(table);
	initialize_philos(table);
	initialize_dinner(table);
}
