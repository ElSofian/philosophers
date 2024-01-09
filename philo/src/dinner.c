/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:39:12 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 14:10:55 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	dinner_alone(void)
{
	return ;
}

static void eat(t_philo *philo)
{
	mutex(&philo->right_fork->mutex, LOCK);
	set_status(philo, TAKE_RIGHT_FORK);
	mutex(&philo->left_fork->mutex, LOCK);
	set_status(philo, TAKE_LEFT_FORK);
	set_long(&philo->mutex, &philo->last_eat, get_time(MILLISECONDS));
	philo->eated_count++;
	set_status(philo, EATING);
	wait(philo->table, philo->table->time_to_eat);
	if (philo->table->eat_count == philo->eated_count)
		set_bool(&philo->mutex, &philo->max_eated, true);
	mutex(&philo->right_fork->mutex, UNLOCK);
	mutex(&philo->left_fork->mutex, UNLOCK);
}

static void	sleeping(t_philo *philo)
{
	set_status(philo, SLEEPING);
	wait(philo->table, philo->table->time_to_sleep);
}

void	wait_all_threads(t_table *table)
{
	while (!get_bool(&table->mutex, &table->can_start))
		;
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->table);
	while (!is_finished(philo->table))
	{
		if (philo->max_eated)
			break ;
		eat(philo);
		sleeping(philo);
		set_status(philo, THINKING);
	}
	return (NULL);
}

void	start(t_table *table)
{
	int	i;

	// if (table->philos_count == 1)
	// 	thread(&table->philo->thread, dinner_alone, &table->philo[0], CREATE);
	i = -1;
	while (++i < table->philos_count)
		thread(&table->philo[i].thread, dinner, &table->philo[i], CREATE);
	table->start_time = get_time(MILLISECONDS);
	set_bool(&table->mutex, &table->can_start, true);
	i = -1;
	while (++i < table->philos_count)
		thread(&table->philo[i].thread, NULL, NULL, JOIN);
	// set_bool(&table->mutex, &table->finished, true);
}