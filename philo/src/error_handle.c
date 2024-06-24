/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:55 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/24 15:51:35 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

static void	thread_error(int status, t_code code)
{
	if (EAGAIN == status)
		error_exit("No resources to create another thread");
	if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == code)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == code || DETACH == code))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies the calling thread.");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *data,
		t_code code)
{
	if (CREATE == code)
		thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (JOIN == code)
		thread_error(pthread_join(*thread, NULL), code);
	else if (DETACH == code)
		thread_error(pthread_detach(*thread), code);
	else
		error_exit("Wrong code for thread_handle: use <CREATE> <JOIN> <DETACH>");
}

static void	handle_mutex_error(t_code code, int status)
{
	if (EINVAL == status && (LOCK == code || UNLOCK == code))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == code)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock could occur if the thread "
					"blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

void	*safe_mutex_handle(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), code);
	else
		return(error_exit("Mutex was fucked up biatch"));
}

void	*safe_malloc(size_t bytes)
{
	void	*target;

	target = malloc(bytes);
	if (!target)
		return (error_exit("Error with the allocation"));
	return (target);
}
