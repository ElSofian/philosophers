/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:27:21 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 13:19:22 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_table	table;

	check(ac, av);
	initialize(&table, ac, av);
	if (table.eat_count == 0)
		return (0);
	start(&table);
	free_all(&table);
	return (0);
}
