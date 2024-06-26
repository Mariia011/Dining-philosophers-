/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:58:42 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/26 15:29:53 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

static void	wait_till_all_ready(t_terms *table)
{
	while(false == table->if_ready);
	gettimeofday(table->start_simulation);
}

static void take_a_fork(t_philo *philo)
{
	
}

void *start_dinner(void *data)
{
	t_philo* philo = (t_philo*)data;
	int i = 0;

	wait_till_all_ready(philo->table);
	distribution(philo);

	return NULL;
}

//module containing setters and getters

void distribution(t_philo *philo)
{
	if(!philo->id % 2)
	{
		take_a_fork(philo, philo->right_fork);
		// take_a_fork(philo, philo->left_fork);
		shift_a_flag(philo->philo_mutex);
	}
	else if(philo->id % 2 != 0)
	{
		take_a_fork(philo, philo->left_fork);
		// take_a_fork(philo, philo->right_fork);
		shift_a_flag(philo->philo_mutex);
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
