/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/04 18:02:43 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	thinking(t_philo *philo)
{
	__lock(philo);
	philo_status(THINK, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	__unlock(philo);
}

static void sleep()
{
	__lock(philo);
	philo_status(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
	__unlock(philo);
}

void set_timeval(t_philo *philo, long *last_time)
{
	__lock(&philo->philo_mutex);
	*last_time = get_time(MILLISECONDS);
	__unlock(&philo->philo_mutex);
}


void	*dinner_simulation(void *data)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)data;
	i = 0;
	wait_till_all_ready(philo->table);
	increase_active_threads(&philo->table->table_mutex, &philo->table->active_threads);
	while (!is_finished(philo->table))
	{
		if (is_full(philo))
			break ;
		eat(philo);
		sleep(philo);
		think(philo);
	}
	return NULL;
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
		// printf("thread of philo %d has been created\n", i + 1);
		i++;
	}
	shift_flag(&table->table_mutex, &table->if_ready, true);
	while (i < table->philo_nbr)
	{
		__thread_join(&table->philos[i].thread);
		i++;
	}
}

// void end_dinner(t_terms *table)
// {
// 	int i = 0;
// 	while(i < table->philo_nbr)
// 	{
// 		free(&table->forks[i]);
// 		free(&table->philos[i]);
// 		i++;
// 	}
// }
