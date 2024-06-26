/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:16:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/26 16:51:58 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

void shift_flag(t_mtx *mtx, bool *dest, const bool src) //setters
{
	safe_mutex_handle(mtx, LOCK);
	*dest = src;
	//maybe add a wait
	safe_mutex_handle(mtx, UNLOCK);
}

void

void	safe_mutex_handle(t_mtx *mutex, t_code code)
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
		error_exit("Mutex was fucked up :3");
}

void	safe_thread_handle(pthread_t *thread, t_fptr foo, void *data,
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

void	*safe_malloc(size_t bytes)
{
	void	*target;

	target = malloc(bytes);
	if (!target)
		error_exit("Error with the allocation");
	return (target);
}

