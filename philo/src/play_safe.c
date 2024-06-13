/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_safe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:55 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/13 19:32:30 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

void *safe_mutex_handle(t_mutex *mutext, t_code code)
{

}

void *safe_malloc(size_t bytes)
{
	void *target;
	target = malloc(bytes);
	if(!target)
		return(error_exit("Error with the allocation"));
	return (target);
}
