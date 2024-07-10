/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_wrappers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:10:14 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/10 19:57:19 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	safe_thread_handle(pthread_t *thread, t_fptr foo, void *data,
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

void	increase_active_threads(t_mtx *mutex, int *val)
{
	__lock(mutex);
	(*val)++;
	__unlock(mutex);
}

void	__thread_join(pthread_t *thread)
{
	safe_thread_handle(thread, NULL, NULL, JOIN);
}

void	__thread_detach(pthread_t *thread)
{
	safe_thread_handle(thread, NULL, NULL, DETACH);
}

void	__thread_create(pthread_t *thread, t_fptr foo, void *data)
{
	safe_thread_handle(thread, foo, data, CREATE);
}
