/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soelalou <soelalou@42.student.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 09:24:56 by soelalou          #+#    #+#             */
/*   Updated: 2023/12/27 09:24:56 by soelalou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <stdbool.h>
# include <errno.h>
# include "../libft/libft.h"

typedef enum e_mutex_code {
	LOCK,
	UNLOCK,
	DESTROY,
	INIT
}	t_mutex_code;

typedef enum e_thread_code {
	CREATE,
	DETACH,
	JOIN
}	t_thread_code;

typedef enum e_time_code {
	SECONDS,
	MILLISECONDS,
	MICROSECONDS
}	t_time_code;

typedef enum e_philo_state {
	EATING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	SLEEPING,
	THINKING,
	DEAD
}	t_philo_state;

typedef struct s_fork
{
	long			id;
	bool			using;
	pthread_mutex_t	mutex;
	struct s_table	*table;
	struct s_fork	*next;
}		t_fork;

typedef struct s_philo
{
	long			id;
	long			eated_count;
	long			last_eat;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	bool			max_eated;
	t_fork			*left_fork;
	t_fork			*right_fork;
	pthread_t		thread;
	pthread_mutex_t	mutex;
	struct s_table	*table;
	struct s_philo	*next;
}		t_philo;

typedef struct s_table
{
	long			philos_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_count;
	long			start_time;
	bool			finished;
	bool			can_start;
	t_fork			*fork;
	t_philo			*philo;
	pthread_mutex_t	mutex;
	pthread_mutex_t	slate;
}			t_table;

// Dinner
void	error(char *str, t_table *table);
void	free_all(t_table *table);
void	check(int ac, char **av);
void	logs(t_philo *philo, char *action);
void	initialize(t_table *table, int ac, char **av);
void	mutex(pthread_mutex_t *mutex, t_mutex_code code);
void	thread(pthread_t *thread, void *(*f)(void *), void *data, t_thread_code code);
void	*dinner(void *data);
void	start(t_table *table);

// Utils
void	lstadd_back_philo(t_philo **lst, t_philo *new_lst);
void	lstadd_back_fork(t_fork **lst, t_fork *new_lst);
void	set_bool(pthread_mutex_t *mtx, bool *dest, bool value);
void	wait(t_table *table, long sec);
void	set_long(pthread_mutex_t *mtx, long *dest, long value);
void	set_status(t_philo *philo, t_philo_state status);
bool	get_bool(pthread_mutex_t *mtx, bool *value);
bool	is_finished(t_table *table);
long	get_long(pthread_mutex_t *mtx, long *value);
long	get_time(t_time_code code);
t_philo	*lstlast_philo(t_philo *lst);
t_fork	*lstlast_fork(t_fork *lst);

#endif