/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:30:11 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 16:58:46 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	initialize_table(t_table *table, int ac, char **av)
{
	table->philos_count = ft_atol(av[1]);
	table->time_to_die = ft_atol(av[2]) * 1e3;
	table->time_to_eat = ft_atol(av[3]) * 1e3;
	table->time_to_sleep = ft_atol(av[4]) * 1e3;
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

static void	put_fork(t_table *table, t_philo *philo, int pos)
{
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &table->fork[pos];
		philo->left_fork = &table->fork[(pos + 1) % table->philos_count];
	}
	else
	{
		philo->right_fork = &table->fork[(pos + 1) % table->philos_count];
		philo->left_fork = &table->fork[pos];
	}
}

static void	initialize_philos(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = 0;
	philo = NULL;
	philo = (t_philo *)malloc(sizeof(t_philo) * table->philos_count);
	if (!philo)
		error("An error occured while allocating philo.", table);
	while (i < table->philos_count)
	{
		philo = table->philo + i;
		philo->id = i + 1;
		philo->eated_count = 0;
		philo->eating = false;
		philo->sleeping = false;
		philo->thinking = false;
		philo->max_eated = false;
		mutex(&philo->mutex, INIT);
		philo->table = table;
		put_fork(table, philo, i);
		i++;
	}
}

void	initialize(t_table *table, int ac, char **av)
{
	initialize_table(table, ac, av);
	initialize_forks(table);
	initialize_philos(table);
}
