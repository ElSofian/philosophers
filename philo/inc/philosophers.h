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
# include "../libft/libft.h"

typedef struct s_fork
{
	bool			using;
	// pthread_mutex_t	mutex;
}		t_fork;

typedef struct s_philo
{
	long			id;
	long			eated_count;
	bool			eating;
	bool			sleeping;
	bool			thinking;
	t_fork			*fork;
	struct s_philo	*next;
}		t_philo;

typedef struct s_table
{
	long		philos_count;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	long		eat_count;
	t_philo		*philo;
	t_philo		*next_to_die;
	t_philo		*next_to_eat;
	pthread_t	*threads;
}			t_table;

void	error(char *str, t_table *table);
void	free_all(t_table *table);
void	check(t_table *table, int ac, char **av);
void	logs(t_philo *philo, char *action);
void	initialize(t_table *table, int ac, char **av);
void	lstadd_back(t_philo **lst, t_philo *new_lst);
t_philo	*lstlast(t_philo *lst);

#endif