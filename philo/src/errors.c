/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:51:09 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 14:36:49 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *str, t_table *table)
{
	ft_printf("Error: %s\n", str);
	if (table)
		free_all(table);
	exit(EXIT_FAILURE);
}
