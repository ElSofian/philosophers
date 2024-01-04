/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:30:11 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 15:14:38 by soelalou         ###   ########.fr       */
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
}

static void	initialize_fork(t_table *table, t_philo *philo)
{
	t_fork	*fork;

	fork = NULL;
	fork = (t_fork *)malloc(sizeof(t_fork));
	if (!fork)
		error("An error occured while allocating fork.", table);
	fork->using = false;
	philo->fork = fork;
}

static void	initialize_philos(t_table *table)
{
	long	i;
	t_philo	*philo;

	i = 0;
	philo = NULL;
	while (i < table->philos_count)
	{
		philo = (t_philo *)malloc(sizeof(t_philo));
		if (!philo)
			error("An error occured while allocating philo.", table);
		philo->id = i + 1;
		printf("Philosopher %ld created.\n", philo->id);
		philo->eated_count = 0;
		philo->eating = false;
		philo->sleeping = false;
		philo->thinking = false;
		initialize_fork(table, philo);
		philo->next = NULL;
		lstadd_back(&table->philo, philo);
		free(philo);
		i++;
	}
}

void	initialize(t_table *table, int ac, char **av)
{
	initialize_table(table, ac, av);
	initialize_philos(table);
}
