/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:56:49 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/05 18:58:28 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	shift_flag(t_mtx *mtx, bool *dest, const bool src) // setters
{
	__lock(mtx);
	*dest = src;
	__unlock(mtx);
}

void	*get_any_val(t_mtx *mutex, void *src)
{
	void	*value;

	__lock(mutex);
	value = src;
	__unlock(mutex);
	return (value);
}

bool	is_full(t_philo *philo)
{
	bool	res;

	__lock(&philo->philo_mutex);
	res = philo->is_full;
	__unlock(&philo->philo_mutex);
	return (res);
}

