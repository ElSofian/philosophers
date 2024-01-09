/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 13:51:09 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 14:12:54 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	error(char *str, t_table *table)
{
	printf("Error: %s\n", str);
	if (table)
		free_all(table);
	exit(EXIT_FAILURE);
}
