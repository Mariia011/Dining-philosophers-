/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/07 22:03:54 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	philo_sleep(t_philo *philo)
{
	philo_status(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

static void calculate_think(t_philo *philo)
{
	long	val;

	val = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (val > 0)
		ft_usleep(val / 2, philo->table);
}

static void	__desynchro(t_philo *philo)
{
	if (philo->table->philo_nbr % 2 == 0 && (philo->id % 2 == 0))
		ft_usleep(30 * MILLISECONDS, philo->table);
	if (philo->table->philo_nbr % 2 != 0 && (philo->id % 2 != 0))
		calculate_think(philo);
}

static void	think(t_philo *philo)
{
	philo_status(THINK, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
 	calculate_think(philo);
}

static void	wait_till_all_ready(t_terms *table)
{
	
	while(false == get_bool(&(table->table_mutex), table->if_ready))
			;
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
	
	increase_active_threads(&philo->table->table_mutex,
		&philo->table->active_threads);
	__desynchro(philo);
	while (!is_finished(philo->table))
	{
		if (is_full(philo))
			break ;
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
		__thread_create(&table->philos[i].thread, dinner_simulation, table->philos + i);
		i++;
	}
	__thread_create(&(table->pahest), pahest_simulation, table);
	// printf("pahest has been created\n");
	shift_flag(&table->table_mutex, &table->if_ready, true);
	
	set_timeval(&table->table_mutex, &table->start_simulation);

	i = 0;
	while (i < table->philo_nbr)
	{
		__thread_join(&table->philos[i].thread);
		i++;
	}
	printf("done\n");
	shift_flag(&table->table_mutex, &table->the_end, true);
	// __thread_join(&(table->pahest));
}
