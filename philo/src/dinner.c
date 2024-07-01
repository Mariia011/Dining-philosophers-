/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 21:02:43 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	thinking(t_philo *philo)
{
	philo_status(THINK, philo);
}

static void	eat(t_philo *philo)
{
	__lock(&philo->right_fork->fork);
	philo_status(TAKE_FORK, philo);
	__lock(&philo->left_fork->fork);
	philo_status(TAKE_FORK, philo);
	philo->meal_counter++;
	philo_status(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	if (has_remained(&philo->table->times_each_eat)
		&& philo->meal_counter == value(&philo->table->times_each_eat))
		set_val(&(philo->mtx), &(philo->full), true);
	__unlock(&philo->right_fork->fork);
	__unlock(&philo->left_fork->fork);
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
	distribution(philo->table);
	while (!is_finished(philo->table))
	{
		if (is_full(philo))
			break ;
		eat(philo);
	}
}

void	start_dinner(t_terms *table)
{
	int	i;

	i = 0;
	if (0 == table->philo_nbr)
		return ;
	if (1 == table->philo_nbr)
		// todo
		// maybe it should be here   philo_to thread(table);
		while (i < table->philos[i])
		{
			__thread_join(&table->philos[i].thread);
			i++;
		}
	__thread_create(&table->philos[i].thread_id, NULL, NULL);
	return (NULL);
}

static void	take_a_fork(t_philo *philo)
{
}

void	distribution(t_philo *philo)
{
	if (!philo->id % 2)
	{
		take_fork(philo, philo->right_fork);
		shift_flag(philo->philo_mutex);
	}
	else if (philo->id % 2 != 0)
	{
		take_a_fork(philo, philo->left_fork);
		shift_flag(philo->philo_mutex);
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
