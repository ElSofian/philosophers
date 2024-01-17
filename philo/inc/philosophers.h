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

# ifndef VISUALIZER
#  define VISUALIZER true
# endif

# define END	"\033[0m"
# define RED	"\033[1;31m"
# define BLUE	"\033[1;34m"
# define GREEN	"\033[1;32m"

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

typedef enum e_philo_state {
	EATING,
	TAKE_RIGHT_FORK,
	TAKE_LEFT_FORK,
	SLEEPING,
	THINKING,
	DEAD
}	t_philo_state;

typedef struct s_philo
{
	long			id;
	long			left_fork;
	long			right_fork;
	long			eated_count;
	bool			max_eated;
	long long		last_eat;
	pthread_t		thread;
	struct s_table	*table;
}		t_philo;

typedef struct s_table
{
	long			philos_count;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			eat_count;
	bool			all_max_eated;
	bool			finished;
	bool			can_start;
	long long		start_time;
	t_philo			philos[200];
	pthread_mutex_t	eating;
	pthread_mutex_t	forks[200];
	pthread_mutex_t	status;
}			t_table;

// Dinner
void		destroy(t_table *table);
void		error(char *str, t_table *table);
void		check(int ac, char **av);
void		initialize(t_table *table, int ac, char **av);
void		mutex(t_table *table, pthread_mutex_t *mutex,
				t_mutex_code code);
void		thread(t_table *table, pthread_t *thread,
				void *(*f)(void *), void *data, t_thread_code code);
void		*dinner(void *data);
void		start(t_table *table);

// Utils
void		searcher(t_table *table, t_philo *philo);
void		set_status(t_philo *philo, t_philo_state status,
					bool visualizer);
void		wait(t_table *table, long long time);
long long	get_time(void);

#endif