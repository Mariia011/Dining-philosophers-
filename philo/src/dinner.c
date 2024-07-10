/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/10 20:04:35 by marikhac         ###   ########.fr       */
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

void	calculate_think(t_philo *philo)
{
	long	val;

	val = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (val > 0)
		ft_usleep(val / 2, philo->table);
}

void	set_timeval(t_mtx *mutex, long *last_time)
{
	__lock(mutex);
	*last_time = get_time(MILLISECONDS);
	__unlock(mutex);
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

void	start_dinner(t_terms *table)
{
	int	i;

	i = 0;
	if (0 == table->philo_nbr)
		return ;
	while (i < table->philo_nbr)
	{
		__thread_create(&table->philos[i].thread, dinner_simulation,
			table->philos + i);
		i++;
	}
	set_timeval(&table->table_mutex, &table->start_simulation);
	shift_flag(&table->table_mutex, &table->if_ready, true);
	__thread_create(&(table->pahest), pahest_simulation, table);
	i = 0;
	while (i < table->philo_nbr)
	{
		__thread_join(&(table->philos[i].thread));
		i++;
	}
	shift_flag(&table->table_mutex, &table->the_end, true);
	__thread_join(&(table->pahest));
}
