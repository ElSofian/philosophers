/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   searcher.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 14:11:29 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 14:17:13 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_all_max_eated(t_table *table)
{
	long	i;

	i = 0;
	while (table->eat_count > 0 && i < table->philos_count
		&& table->philos[i].eated_count >= table->eat_count)
		i++;
	if (i == table->philos_count)
		table->all_max_eated = true;
}

void	searcher(t_table *table, t_philo *philo)
{
	long	i;

	while (!table->all_max_eated)
	{
		i = -1;
		while (++i < table->philos_count && !table->finished)
		{
			mutex(table, &table->eating, LOCK);
			if (get_time() - philo[i].last_eat > table->time_to_die)
			{
				set_status(&philo[i], DEAD, VISUALIZER);
				table->finished = true;
			}
			mutex(table, &table->eating, UNLOCK);
			usleep(100);
		}
		if (table->finished)
			break ;
		check_all_max_eated(table);
	}
}
