/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:55 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/10 20:06:25 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	error_exit(char const *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

void	thread_error(int status, t_code code)
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
		error_exit("No thread could be found corresponding to that specified by"
			"the given threa d ID, thread.");
	else if (EDEADLK == status)
		error_exit("A deadlock was detected or the value of thread specifies"
			"the calling thread.");
}

void	handle_mutex_error(int status, t_code code)
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
		error_exit("The process cannot allocate enough"
			"memory to create another mutex.");
	else if (EBUSY == status)
		error_exit("Mutex is locked");
}
