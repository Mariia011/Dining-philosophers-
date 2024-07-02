/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:56:49 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/02 14:35:26 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

// t_time get_time(t_mtx *mutex, t_time val)
// {
// 	t_time res;
// 	__lock(&mutex);
// 	res = val;
// 	__unlock(&mutex);
// }

void shift_flag(t_mtx *mtx, bool *dest, const bool src) //setters
{
	__lock(mtx);
	*dest = src;
	__unlock(mtx);
}

void *get_any_val(t_mtx *mutex, void *src)
{
	void *value;
	__lock(mutex);
	value = src;
	__unlock(mutex);
	return (value);
}

bool	philo_died(t_philo *philo)
{
	t_time	val;
	t_time	max;

	if (is_full(philo))
		return (false);
	val = get_time(MILLISECONDS) - (long)get_any_val(&philo->philo_mutex,
			&philo->last_meal_time);
	max = philo->table->time_to_die;
	if (val > max)
		return (true);
	return (false);
}

bool is_full(t_philo *philo)
{
	bool res;
	__lock(&philo->philo_mutex);
	res = philo->is_full;
	__unlock(&philo->philo_mutex);
	return res;
}

bool is_finished(t_terms *table)
{
	bool res;
	__lock(&table->table_mutex);
	res = table->the_end;
	__unlock(&table->table_mutex);
	return res;
}

