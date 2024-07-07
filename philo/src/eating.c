/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eating.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 17:38:03 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/07 22:02:04 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static bool	has_remained(int n)
{
	return (n > 0);
}

void	eat(t_philo *philo)
{
	t_fork *forks[2];
	size_t first;
	size_t second;

	forks[1] = philo->right_fork;
	forks[0] = philo->left_fork;

	first = (philo->id % 2 == 0);

	second = !first;

	__lock(&(forks[first]->fork));
	philo_status(TAKE_FORK, philo);
	__lock(&(forks[second]->fork));
	philo_status(TAKE_FORK, philo);
	
	philo->meal_counter++;

	philo_status(EAT, philo);
	ft_usleep(philo->table->time_to_eat, philo->table);
	//write a function to set a timestamp
	set_timeval(&(philo->philo_mutex), &philo->last_meal_time);
	
	if (has_remained(philo->table->nbr_limit_meals) && philo->meal_counter == philo->table->nbr_limit_meals)
	{
		shift_flag(&(philo->philo_mutex), &(philo->is_full), true);
	}
	
	__unlock(&(forks[first]->fork));
	__unlock(&(forks[second]->fork));
}
