/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 14:04:40 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 14:21:35 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	logs(t_philo *philo, char *action)
{
	ft_printf("[%d] %d is %s\n", 23, philo->id, action);
}
