/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bool_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:56:49 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 21:13:29 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	philo_died(t_philo *philo)
{
	t_time	val;
	t_time	max;

	if (get_bool(&philo->philo_mutex, &philo->is_full))
		return (false);
	val = get_time(MILLISECONDS) - get_long(&philo->philo_mutex,
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

