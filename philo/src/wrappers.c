/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:16:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/25 21:20:15 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"


void shift_flag(t_mtx *mtx, bool *dest, const bool src)
{
	safe_mutex_handle(mtx, LOCK);
	*dest = src;
	safe_mutex_handle(mtx, UNLOCK);
}
