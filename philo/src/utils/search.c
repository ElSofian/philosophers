/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:11:29 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/14 15:03:27 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool	can_start_search(t_table *table, pthread_mutex_t *mtx)
{
	int	res;

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
	t_table *tmp;
	
	tmp = (t_table *)data;
	while (!can_start_search(tmp, &tmp->mutex))
		;
	while (!is_finished(tmp))
	{
		i = 0;
		while (i < tmp->philos_count)
		{
			if (philo_is_dead(tmp->philo + i) && !is_finished(tmp))
			{
				set_bool(&tmp->mutex, &tmp->finished, true);
				set_status(tmp->philo + i, DEAD, VISUALIZER);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}