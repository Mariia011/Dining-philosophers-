/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:56:49 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/08 19:41:57 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	shift_flag(t_mtx *mtx, bool *dest, const bool src) // setters
{
	__lock(mtx);
	*dest = src;
	__unlock(mtx);
}

int	get_int(t_mtx *mutex, int *src)
{
	int		value;

	__lock(mutex);
	value = *src;
	__unlock(mutex);

	return (value);
}

long	get_long(t_mtx *mutex, long *src)
{
	long		value;
	__lock(mutex);
	value = *src;
	__unlock(mutex);

	return (value);
}

bool get_bool(t_mtx *mutex, bool *src) //getters
{
	bool value;

	__lock(mutex);
	value = *src;
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

