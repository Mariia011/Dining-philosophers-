/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:28 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 21:11:45 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifndef PHILOS
#  define PHILOS 6
# endif

# define PHILO_MAX 200
# define TIME_MIN 60

# define PHILO_NUMBER 1
# define TIME_TO_DIE 2
# define TIME_TO_EAT 3
# define TIME_TO_SLEEP 4
# define COUNT_OF_MEALS 5
// colors
# define PURPLE "\033[1;35m"
# define YELLOW "\033[1;33m"
# define RESET "\033[0m"

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

typedef void			*(*t_fptr)(void *);

typedef struct s_fork	t_fork;
typedef pthread_mutex_t	t_mtx;
typedef enum e_timecode	t_timecode;

struct					s_fork
{
	t_mtx				fork;
	int					fork_id;
};

struct					s_philo
{
	int					id;
	bool				is_full;
	long				meal_counter;
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
	int					active_threads;
	t_time				start_simulation;
	bool				the_end;
	bool				if_ready;
	pthread_t			pahest;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx table_mutex; // to avoid races while readin data
	t_mtx				write_mutex;
};

bool					philo_died(t_philo *philo);
bool					is_full(t_philo *philo);
bool					is_finished(t_terms *table);

void					__lock(t_mtx *mutex);
void					__unlock(t_mtx *mutex);
void					mutex_init(t_mtx *mutex);
void					mutex_destroy(t_mtx *mutex);

void					*safe_malloc(size_t bytes);
void					table_init(t_terms *table, char **argv);

char					*valid_input(const char *str);
long					ft_atol(const char *str);

void					philo_to_thread(t_terms *table);
void					terms_parse(t_terms *the_table, char **argv);

void					shift_flag(t_mtx *mtx, bool *dest, const bool src);

void					end_dinner(t_terms *table);
void	*start_dinner(void *data); // fix

int						error_exit(char const *str);
void					handle_mutex_error(int status, t_code code);
void					thread_error(int status, t_code code);

enum					e_timecode
{
	MILLISECONDS = 1000,
	MICROSECONDS = 1000000,
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
	EAT,
	SLEEP,
	THINK,
	TAKE_FORK,
	DIE
};

#endif
