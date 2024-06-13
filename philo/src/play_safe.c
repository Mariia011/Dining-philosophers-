/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:55 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/13 20:45:52 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

static void thread_error(int status, t_code code)
{
	if(status == 0)
		return ;
	else if (EAGAIN == status)
		error_exit("No resources to create another thread");
	else if (EPERM == status)
		error_exit("The caller does not have appropriate permission\n");
	else if (EINVAL == status && CREATE == code)
		error_exit("The value specified by attr is invalid.");
	else if (EINVAL == status && (JOIN == opcode || DETACH == opcode))
		error_exit("The value specified by thread is not joinable\n");
	else if (ESRCH == status)
		error_exit("No thread could be found corresponding to that specified by the given thread ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies the calling thread.");
}

static void mutex_error_handle(t_code code, int status)
{
	if(status == 0)
		return ;
	if (EINVAL == status && (LOCK == code || UNLOCK == code))
		error_exit("The value specified by mutex is invalid");
	else if (EINVAL == status && INIT == code)
		error_exit("The value specified by attr is invalid.");
	else if (EDEADLK == status)
		error_exit("A deadlock would occur if the thread "
			"blocked waiting for mutex.");
	else if (EPERM == status)
		error_exit("The current thread does not hold a lock on mutex.");
	else if (ENOMEM == status)
		error_exit("The process cannot allocate enough memory to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *),	void *data, t_code code)
{
	if (CREATE == code)
		handle_thread_error(pthread_create(thread, NULL, foo, data), code);
	else if (JOIN == code)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (DETACH == code)
		handle_thread_error(pthread_detach(*thread), code);
	else
		error_exit("Wrong code for thread_handle: use <CREATE> <JOIN> <DETACH>");
}

void *safe_mutex_handle(t_mutex *mutext, t_code code)
{
	if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else
		error_exit("");
}

void *safe_malloc(size_t bytes)
{
	void *target;
	target = malloc(bytes);
	if(!target)
		return(error_exit("Error with the allocation"));
	return (target);
}
