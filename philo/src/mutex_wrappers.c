/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_wrappers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/30 20:10:25 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 20:43:59 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	safe_mutex_handle(t_mtx *mutex, t_code code)
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
	safe_mutex_handle(mutex, INIT);
}
