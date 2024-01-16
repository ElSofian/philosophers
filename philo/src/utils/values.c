/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   values.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 11:50:35 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/16 12:38:56 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	set_bool(pthread_mutex_t *mtx, bool *dest, bool value)
{
	mutex(mtx, LOCK);
	*dest = value;
	mutex(mtx, UNLOCK);
}

bool	get_bool(pthread_mutex_t *mtx, bool *value)
{
	bool	res;

	mutex(mtx, LOCK);
	res = *value;
	mutex(mtx, UNLOCK);
	return (res);
}

void	increase_long(pthread_mutex_t *mtx, long *value)
{	
	mutex(mtx, LOCK);
	(*value)++;
	mutex(mtx, UNLOCK);
}

void	set_long(pthread_mutex_t *mtx, long *dest, long value)
{
	mutex(mtx, LOCK);
	*dest = value;
	mutex(mtx, UNLOCK);
}

long		get_long(pthread_mutex_t *mtx, long *value)
{
	long	res;

	mutex(mtx, LOCK);
	res = *value;
	mutex(mtx, UNLOCK);
	return (res);
}

bool	is_finished(t_table *table)
{
	return (get_bool(&table->mutex, &table->finished));
}