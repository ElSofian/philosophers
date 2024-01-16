/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:11:29 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 17:59:39 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	can_start_search(t_table *table, pthread_mutex_t *mtx)
{
	bool	res;

	res = false;
	mutex(mtx, LOCK);
	if (table->threads == table->philos_count)
		res = true;
	mutex(mtx, UNLOCK);
	return (res);
}

static bool	philo_is_dead(t_philo *philo)
{
	long	last_eat;
	long	time;
	long	time_without_eating;

	if (get_bool(&philo->mutex, &philo->max_eated))
		return (false);
	last_eat = get_long(&philo->mutex, &philo->last_eat);
	time = get_time(MILLISECONDS);
	time_without_eating = time - last_eat;
	if (time_without_eating > (philo->table->time_to_die / 1000))
		return (true);
	return (false);
}

void	*search(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	while (!can_start_search(table, &table->mutex))
		;
	while (!is_finished(table))
	{
		i = 0;
		while (i < table->philos_count && !is_finished(table))
		{
			if (philo_is_dead(table->philo + i))
			{
				set_bool(&table->mutex, &table->finished, true);
				set_status(table->philo + i, DEAD, VISUALIZER);
			}
			i++;
		}
	}
	return (NULL);
}
