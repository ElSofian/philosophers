/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:04:40 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 13:12:47 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	logs(t_philo *philo, char *action)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - get_time(SECONDS);
	printf("[%ld] Philosopher %ld is %s\n", time, philo->id, action);
}
