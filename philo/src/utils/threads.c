/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:28:52 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/17 14:14:40 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_error(t_table *table, int status, t_thread_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && code == CREATE)
		error("Invalid thread provided.", table);
	else if (status == EINVAL && (code == JOIN || code == DETACH))
		error("The thread is not getable.", table);
	else if (status == EDEADLK)
		error("A deadlock will occur if the operation is performed.", table);
	else if (status == EPERM)
		error("Caller doesn't have access permission to this thread.", table);
	else if (status == EAGAIN)
		error("Insufficient ressources to create another thread.", table);
	else if (status == ESRCH)
		error("Thread not found.", table);
}

void	thread(t_table *table, pthread_t *thread,
				void *(*f)(void *), void *data, t_thread_code code)
{
	if (code == CREATE)
		check_error(table, pthread_create(thread, NULL, f, data), code);
	else if (code == JOIN)
		check_error(table, pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		check_error(table, pthread_detach(*thread), code);
	else
		error("Invalid thread code given.", table);
}
