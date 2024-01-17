/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:30:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 14:19:38 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	set_status_visualizer(t_philo *philo, t_philo_state status,
									bool visualizer)
{
	if (!visualizer)
		return (0);
	if (status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK)
		printf("%ld %ld has taken a fork\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == EATING)
		printf("%ld %ld is eating\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == SLEEPING)
		printf("%ld %ld is sleeping\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == THINKING)
		printf("%ld %ld is thinking\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == DEAD)
		printf("%ld %ld died\n",
			get_time() - philo->table->start_time, philo->id);
	return (1);
}

void	set_status(t_philo *philo, t_philo_state status, bool visualizer)
{
	long	time;

	time = get_time() - philo->table->start_time;
	if (philo->table->finished)
		return ;
	mutex(philo->table, &philo->table->status, LOCK);
	if (!set_status_visualizer(philo, status, visualizer))
	{
		if (status == TAKE_RIGHT_FORK)
			printf("[%ld] 🍴 Philosopher %ld has taken his right fork (%ld)\n",
				time, philo->id, philo->right_fork);
		else if (status == TAKE_LEFT_FORK)
			printf("[%ld] 🍴 Philosopher %ld has taken his left fork (%ld)\n",
				time, philo->id, philo->left_fork);
		else if (status == EATING)
			printf("[%ld] 🍝 %sPhilosopher %ld is eating%s (%ld)\n", time,
				BLUE, philo->id, END, philo->eated_count);
		else if (status == SLEEPING)
			printf("[%ld] 💤 Philosopher %ld is sleeping\n", time, philo->id);
		else if (status == THINKING)
			printf("[%ld] 🤔 Philosopher %ld is thinking\n", time, philo->id);
		else if (status == DEAD)
			printf("[%ld] 💀 "RED"Philosopher %ld died"END"\n", time, philo->id);
	}
	mutex(philo->table, &philo->table->status, UNLOCK);
}
