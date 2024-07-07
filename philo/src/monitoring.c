/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:48:03 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/07 22:06:50 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	philo_died(t_philo *philo)
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

bool	is_finished(t_terms *table)
{
	bool	res;

	__lock(&table->table_mutex);
	res = table->the_end;
	__unlock(&table->table_mutex);
	return (res);
}

bool all_threads_running(t_mtx *mutex, t_terms *table)
{
	bool res;
	
	__lock(mutex);

	res = (table->active_threads == table->philo_nbr);
	
	__unlock(mutex);
	
	return res;
}

void	*pahest_simulation(void *data)
{
	t_terms	*table;
	int i;

	table = (t_terms *)data;
	while (!all_threads_running(&table->table_mutex, table))
		;
	while (!is_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !is_finished(table))
		{
			if (philo_died(table->philos))
			{
				shift_flag(&table->table_mutex, &table->the_end, true);
				philo_status(DIE, &table->philos[i]);
			}
			i++;
		}
	}
	return (NULL);
}
