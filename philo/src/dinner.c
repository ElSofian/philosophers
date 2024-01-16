/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:39:12 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 13:46:21 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	can_dinner_start(t_table *table)
{
	while (!get_bool(&table->mutex, &table->can_start))
		;
}

static void	*dinner_alone(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	can_dinner_start(philo->table);
	set_long(&philo->mutex, &philo->last_eat, get_time(MILLISECONDS));
	increase_long(&philo->table->mutex, &philo->table->threads);
	set_status(philo, TAKE_RIGHT_FORK, VISUALIZER);
	while (!is_finished(philo->table))
		usleep(200);
	return (NULL);
}

static void eat(t_philo *philo)
{
	mutex(&philo->right_fork->mutex, LOCK);
	set_status(philo, TAKE_RIGHT_FORK, VISUALIZER);
	mutex(&philo->left_fork->mutex, LOCK);
	set_status(philo, TAKE_LEFT_FORK, VISUALIZER);
	set_long(&philo->mutex, &philo->last_eat, get_time(MILLISECONDS));
	philo->eated_count++;
	set_status(philo, EATING, VISUALIZER);
	wait(philo->table, philo->table->time_to_eat);
	if (philo->table->eat_count == philo->eated_count)
		set_bool(&philo->mutex, &philo->max_eated, true);
	mutex(&philo->right_fork->mutex, UNLOCK);
	mutex(&philo->left_fork->mutex, UNLOCK);
}

void	think(t_philo *philo, bool start)
{
	long	new_time_to_think;
	
	if (!start)
		set_status(philo, THINKING, VISUALIZER);
	if (philo->table->philos_count % 2 == 0)
		return ;
	new_time_to_think = philo->table->time_to_eat * 2
		- philo->table->time_to_sleep;
	if (new_time_to_think < 0)
		new_time_to_think = 0;
	wait(philo->table, new_time_to_think * 0.42);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	can_dinner_start(philo->table);
	set_long(&philo->mutex, &philo->last_eat, get_time(MILLISECONDS));
	increase_long(&philo->table->mutex, &philo->table->threads);
	unsync(philo);
	while (!is_finished(philo->table))
	{
		if (get_bool(&philo->mutex, &philo->max_eated))
			break ;
		eat(philo);
		set_status(philo, SLEEPING, VISUALIZER);
		wait(philo->table, philo->table->time_to_sleep);
		think(philo, false);
	}
	return (NULL);
}

void	start(t_table *table)
{
	int	i;

	if (table->philos_count == 1)
		thread(&table->philo[0].thread, dinner_alone, &table->philo[0], CREATE);
	i = -1;
	while (++i < table->philos_count)
		thread(&table->philo[i].thread, dinner, &table->philo[i], CREATE);
	thread(&table->searcher, search, table, CREATE);
	table->start_time = get_time(MILLISECONDS);
	set_bool(&table->mutex, &table->can_start, true);
	i = -1;
	while (++i < table->philos_count)
		thread(&table->philo[i].thread, NULL, NULL, JOIN);
	set_bool(&table->mutex, &table->finished, true);
	thread(&table->searcher, NULL, NULL, JOIN);
}