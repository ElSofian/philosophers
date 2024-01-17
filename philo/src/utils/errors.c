/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:51:09 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 17:05:43 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy(t_table *table)
{
	long	i;

	i = 0;
	while (i < table->philos_count)
	{
		table->thread_code = JOIN;
		thread(table, &table->philos[i].thread, NULL, NULL);
		i++;
	}
	i = 0;
	while (i < table->philos_count)
	{
		mutex(table, &table->forks[i], DESTROY);
		i++;
	}
	mutex(table, &table->status, DESTROY);
}

void	error(char *str, t_table *table)
{
	printf("Error: %s\n", str);
	if (table)
		destroy(table);
	exit(EXIT_FAILURE);
}
