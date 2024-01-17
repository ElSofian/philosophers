/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 12:30:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 17:02:21 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	set_status_visualizer(t_philo *philo, t_philo_state status,
									bool visualizer)
{
	if (!visualizer)
		return (0);
	if (status == TAKE_RIGHT_FORK || status == TAKE_LEFT_FORK)
		printf("%lld %ld has taken a fork\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == EATING)
		printf("%lld %ld is eating\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == SLEEPING)
		printf("%lld %ld is sleeping\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == THINKING)
		printf("%lld %ld is thinking\n",
			get_time() - philo->table->start_time, philo->id);
	else if (status == DEAD)
		printf("%lld %ld died\n",
			get_time() - philo->table->start_time, philo->id);
	return (1);
}

void	set_status(t_philo *philo, t_philo_state status, bool visualizer)
{
	long long	t;

	t = get_time() - philo->table->start_time;
	if (philo->table->finished)
		return ;
	mutex(philo->table, &philo->table->status, LOCK);
	if (!set_status_visualizer(philo, status, visualizer))
	{
		if (status == TAKE_RIGHT_FORK)
			printf("[%lld] 🍴 Philosopher %ld has taken his right fork (%ld)\n",
				t, philo->id, philo->right_fork);
		else if (status == TAKE_LEFT_FORK)
			printf("[%lld] 🍴 Philosopher %ld has taken his left fork (%ld)\n",
				t, philo->id, philo->left_fork);
		else if (status == EATING)
			printf("[%lld] 🍝 %sPhilosopher %ld is eating%s (%ld)\n", t,
				BLUE, philo->id, END, philo->eated_count);
		else if (status == SLEEPING)
			printf("[%lld] 💤 Philosopher %ld is sleeping\n", t, philo->id);
		else if (status == THINKING)
			printf("[%lld] 🤔 Philosopher %ld is thinking\n", t, philo->id);
		else if (status == DEAD)
			printf("[%lld] 💀 "RED"Philosopher %ld died"END"\n", t, philo->id);
	}
	mutex(philo->table, &philo->table->status, UNLOCK);
}
