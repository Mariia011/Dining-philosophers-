/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:10:53 by aamirkha          #+#    #+#             */
/*   Updated: 2024/07/10 19:56:45 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	fork_destroy(t_fork *fork)
{
	mutex_destroy(&(fork->fork));
}

static void	philo_destroy(t_philo *philo)
{
	mutex_destroy(&(philo->philo_mutex));
}

void	table_destroy(t_terms **table_ptr)
{
	int		i;
	t_terms	*table;

	i = 0;
	table = *table_ptr;
	while (i < table->philo_nbr)
	{
		philo_destroy(&(table->philos[i]));
		fork_destroy(&(table->forks[i]));
		i++;
	}
	mutex_destroy(&(table->table_mutex));
	mutex_destroy(&(table->write_mutex));
	free(table->forks);
	free(table->philos);
	free(table);
	*table_ptr = NULL;
}
