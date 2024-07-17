/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:10:25 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:28:31 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	safe_mutex_handle(t_mtx *mutex, t_code code)
{
	if (code == LOCK)
		assert(pthread_mutex_lock(mutex) == 0);
	else if (code == UNLOCK)
		assert(pthread_mutex_unlock(mutex) == 0);
	else if (code == INIT)
		assert(pthread_mutex_init(mutex, NULL) == 0);
	else if (code == DESTROY)
		assert(pthread_mutex_destroy(mutex) == 0);
}

void	__lock(t_mtx *mutex)
{
	safe_mutex_handle(mutex, LOCK);
}

void	__unlock(t_mtx *mutex)
{
	safe_mutex_handle(mutex, UNLOCK);
}

void	mutex_init(t_mtx *mutex)
{
	safe_mutex_handle(mutex, INIT);
}

void	mutex_destroy(t_mtx *mutex)
{
	safe_mutex_handle(mutex, DESTROY);
}
