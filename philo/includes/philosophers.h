/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:28 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/13 20:18:23 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#ifndef PHILOS
#define PHILOS 6
#endif

#define PHILO_MAX 200
#define MILLISECONDS 1000
typedef struct s_table t_table;
typedef struct s_philo t_philo;
typedef enum e_formut t_code;
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#include <semaphore.h>

enum e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
};

struct s_philo
{
	int				id;
	bool			is_full;
	long			meals_counter;
	long			last_meal_time;
	pthread_t		thread_id;
	t_fork			*first_fork;
	t_fork			*second_fork;
	t_mtx			philo_mutex;
	t_table			*table;
};

struct	s_table
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limit_meals;
	long				philo_nbr;
	long				start_simulation;
	bool				the_end;
	t_philo				*philos;
};

pthread_mutex_t mutex;

int error_exit(char const *str);
void *safe_mutex_handle(t_mutex *mutext, t_code code);



#endif
