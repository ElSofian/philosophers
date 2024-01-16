/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:36:54 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 13:19:29 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_all(t_table *table)
{
	int		i;

	i = 0;
	while (i < table->philos_count)
	{
		mutex(&table->philo[i].mutex, DESTROY);
		i++;
	}
	mutex(&table->status, DESTROY);
	mutex(&table->mutex, DESTROY);
	free(table->fork);
	free(table->philo);
}
