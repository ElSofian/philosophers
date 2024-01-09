/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:30:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 14:07:44 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_status(t_philo *philo, t_philo_state status)
{
	if (philo->max_eated)
		return ;
	mutex(&philo->table->mutex, LOCK);
	if (status == TAKE_RIGHT_FORK && !is_finished(philo->table))
		printf("[%ld] 🍴 Philosopher %ld has taken his right fork\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == TAKE_LEFT_FORK && !is_finished(philo->table))
		printf("[%ld] 🍴 Philosopher %ld has taken his left fork\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == EATING && !is_finished(philo->table))
		printf("[%ld] 🍝 Philosopher %ld is eating\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == SLEEPING && !is_finished(philo->table))
		printf("[%ld] 💤 Philosopher %ld is sleeping\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == THINKING && !is_finished(philo->table))
		printf("[%ld] 🤔 Philosopher %ld is thinking\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	else if (status == DEAD && !is_finished(philo->table))
		printf("[%ld] 💀 Philosopher %ld died\n",
			get_time(MILLISECONDS) - philo->table->start_time, philo->id);
	mutex(&philo->table->mutex, UNLOCK);
}