/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:27:56 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	__desynchro(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0 && (philo->id % 2 == 0))
		ft_usleep(30 * MILLISECONDS, philo->table);
	if (philo->table->philo_nbr % 2 != 0 && (philo->id % 2 != 0))
		calculate_think(philo);
}

void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	wait_till_all_ready(philo->table);
	set_timeval(&(philo->philo_mutex), &philo->last_meal_time);
	increase_active_threads(&philo->table->table_mutex,
		&philo->table->active_threads);
	__desynchro(philo);
	while (!is_finished(philo->table) && !is_full(philo))
	{
		eat(philo);
		philo_sleep(philo);
		think(philo);
	}
	return (NULL);
}

static void	join_table(t_terms *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		__thread_join(&(table->philos[i].thread));
		i++;
	}
}

void	start_dinner(t_terms *table)
{
	int	i;

	i = 0;
	if (0 == table->philo_nbr || (table->nbr_limit_meals != -1
			&& table->nbr_limit_meals < 1))
		return ;
	if (table->philo_nbr == 1)
		__thread_create(&table->philos[0].thread, one_philo_case,
			&(table->philos[0]));
	else
	{
		while (i < table->philo_nbr)
		{
			__thread_create(&table->philos[i].thread, dinner_simulation,
				table->philos + i);
			i++;
		}
	}
	set_timeval(&table->table_mutex, &table->start_simulation);
	shift_flag(&table->table_mutex, &table->if_ready, true);
	__thread_create(&(table->oxrannik), oxrannik_simulation, table);
	join_table(table);
	shift_flag(&table->table_mutex, &table->the_end, true);
	__thread_join(&(table->oxrannik));
}
