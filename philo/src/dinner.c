/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:39:12 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 14:23:13 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
{
	t_table	*table;
	
	table = philo->table;
	mutex(table, &table->forks[philo->left_fork], LOCK);
	set_status(philo, TAKE_LEFT_FORK, VISUALIZER);
	mutex(table, &table->forks[philo->right_fork], LOCK);
	set_status(philo, TAKE_RIGHT_FORK, VISUALIZER);
	mutex(table, &table->eating, LOCK);
	set_status(philo, EATING, VISUALIZER);
	philo->last_eat = get_time();
	mutex(table, &table->eating, UNLOCK);
	wait(table, table->time_to_eat);
	philo->eated_count++;
	mutex(table, &table->forks[philo->left_fork], UNLOCK);
	mutex(table, &table->forks[philo->right_fork], UNLOCK);
}

static void sleeping(t_philo *philo)
{
	set_status(philo, SLEEPING, VISUALIZER);
	wait(philo->table, philo->table->time_to_sleep);
}

static void	think(t_philo *philo)
{
	set_status(philo, THINKING, VISUALIZER);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 != 0)
		usleep(15000);
	while (!philo->table->finished)
	{
		eat(philo);
		if (philo->table->all_max_eated)
			break ;
		sleeping(philo);
		think(philo);
	}
	return (NULL);
}

void	start(t_table *table)
{
	long	i;
	t_philo	*philo;

	if (table->eat_count == 0)
		return ;
	i = 0;
	philo = table->philos;
	table->start_time = get_time();
	while (i < table->philos_count)
	{
		thread(table, &philo[i].thread, dinner, &philo[i], CREATE);
		philo[i].last_eat = get_time();
		i++;
	}
	searcher(table, table->philos);
}