/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:27:21 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 15:13:41 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	*table;

	table = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		error("An error occured while allocating table.", NULL);
	check(table, ac, av);
	initialize(table, ac, av);
	for (int i = 0; i < table->philos_count; i++)
	{
		printf("Philosopher %d:\nId: %ld\nEated: %ld\nEating: %d\nSleeping: %d\nThinking: %d\n\n",
			i, table->philo->id, table->philo->eated_count, table->philo->eating, table->philo->sleeping, table->philo->thinking);
		table->philo = table->philo->next;
	}
	return (0);
}
