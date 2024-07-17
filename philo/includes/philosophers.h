/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:28 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:37:04 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# ifndef PHILOS
#  define PHILOS 6
# endif

# define PHILO_MAX 200
# define TIME_MIN 60000

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
# include <assert.h>

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
	pthread_t			oxrannik;
	t_fork				*forks;
	t_philo				*philos;
	t_mtx				table_mutex;
	t_mtx				write_mutex;
};

// boolean
// bool					is_finished(t_terms *table);
void					shift_flag(t_mtx *mtx, bool *dest, const bool src);
bool					is_full(t_philo *philo);
bool					is_finished(t_terms *table);
bool					get_bool(t_mtx *mutex, bool *src);
bool					philo_died(t_philo *philo);

// mutex wrappers
void					__lock(t_mtx *mutex);
void					__unlock(t_mtx *mutex);
void					mutex_init(t_mtx *mutex);
void					mutex_destroy(t_mtx *mutex);

// wrappers
void					*safe_malloc(size_t bytes);
void					wait_till_all_ready(t_terms *table);
void					think(t_philo *philo);
void					philo_sleep(t_philo *philo);

// parsing helpers
long					ft_atolong(char *str);
char					*valid_input(char *str);
int						get_int(t_mtx *mutex, int *src);
// parsing
t_terms					*terms_parse(int argc, char **argv);

// dinner helpers
long					get_long(t_mtx *mutex, long *src);
void					set_timeval(t_mtx *mutex, long *last_time);
void					*one_philo_case(void *data);
t_terms					*__death(t_terms *table);

// dinner
void					eat(t_philo *philo);
void					start_dinner(t_terms *table);
void					*dinner_simulation(void *data);
void					*oxrannik_simulation(void *data);
void					calculate_think(t_philo *philo);

// thread wrappers
void					increase_active_threads(t_mtx *mutex, int *val);
void					__thread_join(pthread_t *thread);
void					__thread_detach(pthread_t *thread);
void					__thread_create(pthread_t *thread, t_fptr foo,
							void *data);
// error handling
int						error_log(char const *str);
// time
long					get_time(t_timecode time_code);
void					ft_usleep(t_time usec, t_terms *table);
// status
void					philo_status(t_code philo_status, t_philo *philo);
// destroys
void					table_destroy(t_terms **table_ptr);

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
