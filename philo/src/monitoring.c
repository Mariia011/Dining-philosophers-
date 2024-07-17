/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:48:03 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/15 14:52:47 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

bool	philo_died(t_philo *philo)
{
	t_time	val;

	val = 0;
	if (is_full(philo))
		return (false);
	val = get_time(MILLISECONDS) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	return (val > philo->table->time_to_die / MILLISECONDS);
}

bool	is_finished(t_terms *table)
{
	bool	res;

	__lock(&table->table_mutex);
	res = table->the_end;
	__unlock(&table->table_mutex);
	return (res);
}

static bool	all_threads_running(t_terms *table)
{
	return (get_int(&table->table_mutex,
			&table->active_threads) == table->philo_nbr);
}

void	*oxrannik_simulation(void *data)
{
	t_terms	*table;
	int		i;

	table = (t_terms *)data;
	while (!all_threads_running(table))
		;
	while (!is_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !is_finished(table))
		{
			if (philo_died(table->philos + i))
			{
				philo_status(DIE, &table->philos[i]);
				shift_flag(&table->table_mutex, &table->the_end, true);
			}
			i++;
		}
	}
	return (NULL);
}
