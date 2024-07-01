/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:18:37 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 15:19:51 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long get_time(t_timecode time_code)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		error_exit("Bad time");
	if (MILLISECONDS == time_code)
		return (tv.tv_sec * MILLISECONDS + tv.tv_usec / MILLISECONDS);
	else if (MICROSECONDS == time_code)
		return (tv.tv_sec * MICROSECONDS + tv.tv_usec);
	else
		error_exit("Wrong input for time val");
	return (-1);
}

void ft_usleep(t_time usec, t_terms *table)
{
	t_time value;

	value = get_time(MICROSECONDS);
	while(sec > (get_time(MICROSECOND) - value) && !is_finished(table));
		;
}
