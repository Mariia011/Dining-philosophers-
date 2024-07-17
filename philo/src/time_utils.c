/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:18:37 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:28:38 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	set_timeval(t_mtx *mutex, long *last_time)
{
	__lock(mutex);
	*last_time = get_time(MILLISECONDS);
	__unlock(mutex);
}

long	get_time(t_timecode time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		error_log("Bad time");
	if (MILLISECONDS == time_code)
		return (tv.tv_sec * MILLISECONDS + tv.tv_usec / MILLISECONDS);
	else if (MICROSECONDS == time_code)
		return (tv.tv_sec * MICROSECONDS + tv.tv_usec);
	else
		error_log("Wrong input for time val");
	return (-1);
}

void	ft_usleep(t_time usec, t_terms *table)
{
	t_time	value;

	value = get_time(MICROSECONDS);
	while (usec > (get_time(MICROSECONDS) - value) && !is_finished(table))
		;
}
