/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstlast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:05:15 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 10:55:01 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_philo	*lstlast_philo(t_philo *lst)
{
	t_philo	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_fork	*lstlast_fork(t_fork *lst)
{
	t_fork	*tmp;

	tmp = lst;
	while (tmp && tmp->next)
		tmp = tmp->next;
	return (tmp);
}