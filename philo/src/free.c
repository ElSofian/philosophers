/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:54 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 14:41:39 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	if (table->philo)
	{
		i = 0;
		while (i < table->philos_count)
		{
			free(table->philo->fork);
			free(table->philo);
			table->philo = table->philo->next;
		}
		free(table->philo);
	}
	free(table);
}
