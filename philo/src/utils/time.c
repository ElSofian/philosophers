/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:06:45 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 13:43:38 by soelalou         ###   ########.fr       */
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
	long			nb;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	nb = 1;
	if (code == MILLISECONDS)
		nb = 1e3;
	else if (code == MICROSECONDS)
		nb = 1e6;
	else if (code == SECONDS)
	{
		nb = 1e6;
		return (tv.tv_sec + tv.tv_usec / nb);
	}
	else
		error("Wrong input code.", NULL);
	return (tv.tv_sec * nb + tv.tv_usec / nb);
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