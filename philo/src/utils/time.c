/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:06:45 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 14:17:40 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	wait(t_table *table, long sec)
{
	long	start;
	long	passed;
	long	remaining;

	start = get_time(MICROSECONDS);
	while (get_time(MICROSECONDS) - start < sec)
	{
		if (is_finished(table))
			break ;
		passed = get_time(MICROSECONDS) - start;
		remaining = sec - passed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (get_time(MICROSECONDS) - start < sec)
				;
		}
	}
}

long	get_time(int code)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	if (code == MILLISECONDS)
		return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
	else if (code == MICROSECONDS)
		return (tv.tv_sec * 1e6 + tv.tv_usec);
	else if (code == SECONDS)
		return (tv.tv_sec + tv.tv_usec / 1e6);
	else
		error("Wrong input code.", NULL);
	return (0);
}

void	unsync(t_philo *philo)
{
	if (philo->table->philos_count % 2 == 0)
	{
		if (philo->id % 2 == 0)
			wait(philo->table, 300000);
	}
	else
	{
		if (philo->id % 2)
			think(philo, true);
	}
}