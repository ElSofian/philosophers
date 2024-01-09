/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:13:34 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 10:14:38 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	end(t_table *table, char *msg)
{
	free_all(table);
	if (msg)
		ft_printf("%s\n", msg);
	exit(EXIT_SUCCESS);
}