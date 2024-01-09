/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:54 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 13:17:02 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_table *table)
{
	t_philo *philo_tmp;
	t_fork *fork_tmp;
	
	while (table->philo)
	{
		philo_tmp = table->philo;
		table->philo = table->philo->next;
		free(philo_tmp);
	}
	while (table->fork)
	{
		fork_tmp = table->fork;
		table->fork = table->fork->next;
		free(fork_tmp);
	}
	table->fork = NULL;
	table->philo = NULL;
	free(table);
}
