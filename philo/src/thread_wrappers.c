/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_wrappers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:10:14 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:13:52 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	safe_thread_handle(pthread_t *thread, t_fptr foo, void *data,
		t_code code)
{
	if (CREATE == code)
		assert(pthread_create(thread, NULL, foo, data) == 0);
	else if (JOIN == code)
		assert(pthread_join(*thread, NULL) == 0);
	else if (DETACH == code)
		assert(pthread_detach(*thread) == 0);
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
