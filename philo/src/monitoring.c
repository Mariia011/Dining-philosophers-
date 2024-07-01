/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:48:03 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 20:43:56 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*pahest_simulation(void *data)
{
	t_terms	*table;

	table = (t_terms *)data;
	while (!all_threads_running(&table->table_mutex, ))
		;
	while (!is_finished(table))
	{
		i = 0;
		while (i < table->philo_nbr && !is_finished(table))
		{
			if (philo_dead(table->philos))
			{
				shift_flag(&table->table_mutex, &table->the_end, true);
				philo_status(DIE, table->philo_nbr + i);
			}
		}
	}
	return (NULL);
}
