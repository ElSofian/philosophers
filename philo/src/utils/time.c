/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:06:45 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 12:26:04 by soelalou         ###   ########.fr       */
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
		if (remaining > 100)
			usleep(sec / 2);
		else
		{
			while (get_time(MICROSECONDS) - start < sec)
				;
		}
	}
}

long	get_time(t_time_code code)
{
	long			nb;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	nb = 1;
	if (code == MILLISECONDS)
		nb = 1000;
	else if (code == MICROSECONDS)
		nb = 1000000;
	else if (code != SECONDS)
		error("Wrong input code.", NULL);
	return ((tv.tv_sec * nb) + (tv.tv_usec / nb));
}