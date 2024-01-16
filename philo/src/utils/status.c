/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:30:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 13:21:56 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	set_status_visualizer(t_philo *philo, t_philo_state status, bool visualizer)
{
	if (!visualizer)
		return (0);
	if ((status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK)
		&& !is_finished(philo->table))
		printf("%ld %ld has taken a fork\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == EATING && !is_finished(philo->table))
		printf("%ld %ld is eating\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == SLEEPING && !is_finished(philo->table))
		printf("%ld %ld is sleeping\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == THINKING && !is_finished(philo->table))
		printf("%ld %ld is thinking\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == DEAD)
		printf("%ld %ld died\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	return (1);
}

void	set_status(t_philo *philo, t_philo_state status, bool visualizer)
{
	if (get_bool(&philo->mutex, &philo->max_eated))
		return ;
	mutex(&philo->table->status, LOCK);
	if (!set_status_visualizer(philo, status, visualizer))
	{
		if (status == TAKE_RIGHT_FORK && !is_finished(philo->table))
			printf("[%ld] 🍴 Philosopher %ld has taken his right fork (%ld)\n",
				get_time(MILLISECONDS) - philo->table->start_time, philo->id,
				philo->right_fork->id);
		else if (status == TAKE_LEFT_FORK && !is_finished(philo->table))
			printf("[%ld] 🍴 Philosopher %ld has taken his left fork (%ld)\n",
				get_time(MILLISECONDS) - philo->table->start_time, philo->id,
				philo->left_fork->id);
		else if (status == EATING && !is_finished(philo->table))
			printf("[%ld] 🍝 %sPhilosopher %ld is eating%s (%ld)\n",
				get_time(MILLISECONDS) - philo->table->start_time, BLUE, philo->id, END, philo->eated_count);
		else if (status == SLEEPING && !is_finished(philo->table))
			printf("[%ld] 💤 Philosopher %ld is sleeping\n",
				get_time(MILLISECONDS) - philo->table->start_time, philo->id);
		else if (status == THINKING && !is_finished(philo->table))
			printf("[%ld] 🤔 Philosopher %ld is thinking\n",
				get_time(MILLISECONDS) - philo->table->start_time, philo->id);
		else if (status == DEAD)
			printf("[%ld] 💀 %sPhilosopher %ld died%s\n",
				get_time(MILLISECONDS) - philo->table->start_time, RED, philo->id, END);
	}
	mutex(&philo->table->status, UNLOCK);
}
