/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:27:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 14:03:31 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	*table;

	check(ac, av);
	table = NULL;
	table = (t_table *)malloc(sizeof(t_table));
	if (!table)
		error("An error occured while allocating table.", NULL);
	initialize(table, ac, av);
	if (table->eat_count == 0)
		return (0);
	start(table);
	// free_all(table);
	return (0);
}
