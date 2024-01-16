/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:39:12 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 18:00:01 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_philo *philo)
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
	wait(philo->table, new_time_to_think * 0.5);
}

void	*dinner(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!get_bool(&philo->table->mutex, &philo->table->can_start))
		;
	set_long(&philo->mutex, &philo->last_eat, get_time(MILLISECONDS));
	set_long(&philo->table->mutex, &philo->table->threads,
		get_long(&philo->table->mutex, &philo->table->threads) + 1);
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
