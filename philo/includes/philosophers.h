/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:28 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/25 21:21:02 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifndef PHILOS
#  define PHILOS 6
# endif

# define PHILO_MAX 200
# define MILLISECONDS 1000
# define TIME_MIN 60

# define PHILO_NUMBER 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define COUNT_OF_MEALS 5

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef long			t_time;

typedef struct s_terms	t_terms;
typedef struct s_philo	t_philo;
typedef enum e_code		t_code;

typedef void* (*t_fptr)(void*);

typedef struct s_fork	t_fork;
typedef pthread_mutex_t	t_mtx;

struct					s_fork
{
	t_mtx				fork;
	int					fork_id;
};

struct					s_philo
{
	int					id;
	bool				is_full;
	long				meals_counter;
	long				last_meal_time;
	pthread_t			thread;
	t_fork				*right_fork;
	t_fork				*left_fork;
	t_terms				*table;
	t_mtx				philo_mutex;
};

struct					s_terms
{
	t_time				time_to_die;
	t_time				time_to_eat;
	t_time				time_to_sleep;
	long				nbr_limit_meals;
	int					philo_nbr;
	t_time				start_simulation;
	bool				the_end;
	bool 				if_ready;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				mtx;
};



enum					e_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
};

int						error_exit(char const *str);
void					safe_mutex_handle(t_mtx *mutex, t_code code);
void					*safe_malloc(size_t bytes);
void					safe_thread_handle(pthread_t *thread,
							t_fptr foo, void *data, t_code code);
void					table_init(t_terms *table, char **argv);
const char					*valid_input(const char *str);
long					ft_atol(const char *str);


void shift_flag(t_mtx *mtx, bool *dest, const bool src);


void end_dinner(t_terms *table);
void	terms_parse(t_terms *the_table, char **argv);
void *start_dinner(void *data);

#endif
