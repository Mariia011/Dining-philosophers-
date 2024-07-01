/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:16:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 16:52:34 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void shift_flag(t_mtx *mtx, bool *dest, const bool src) //setters
{
	safe_mutex_handle(mtx, LOCK);
	*dest = src;
	safe_mutex_handle(mtx, UNLOCK);
}

void	*safe_malloc(size_t bytes)
{
	void	*target;

	target = malloc(bytes);
	if (!target)
		error_exit("Error with the allocation");
	return (target);
}
