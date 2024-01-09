/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 10:18:12 by soelalou          #+#    #+#             */
/*   Updated: 2024/01/09 10:31:16 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	check_error(int status, t_mutex_code code)
{
	if (status == EINVAL && (code == LOCK || code == UNLOCK))
		error("Invalid mutex provided.", NULL);
	else if (status == EINVAL && code == INIT)
		error("Mutex initializing has failed.", NULL);
	else if (status == EDEADLK)
		error("A deadlock will occur if the operation is performed.", NULL);
	else if (status == EPERM)
		error("The current thread does not own the mutex.", NULL);
	else if (status == ENOMEM)
		error("Insufficient memory to initialize the mutex.", NULL);
	else if (status == EBUSY)
		error("The mutex could not be used because it was already locked.", NULL);
}

void	mutex(pthread_mutex_t *mutex, t_mutex_code code)
{
	if (code == LOCK)
		check_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		check_error(pthread_mutex_unlock(mutex), code);
	else if (code == DESTROY)
		check_error(pthread_mutex_destroy(mutex), code);
	else if (code == INIT)
		check_error(pthread_mutex_init(mutex, NULL), code);
	else
		error("Invalid mutex code given.", NULL);
}