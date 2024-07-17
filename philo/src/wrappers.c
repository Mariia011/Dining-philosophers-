/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:16:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:15:52 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	philo_sleep(t_philo *philo)
{
	philo_status(SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep, philo->table);
}

void	think(t_philo *philo)
{
	philo_status(THINK, philo);
	if (philo->table->philo_nbr % 2 == 0)
		return ;
	calculate_think(philo);
}

void	wait_till_all_ready(t_terms *table)
{
	while (false == get_bool(&(table->table_mutex), &table->if_ready))
		;
}

void	*safe_malloc(size_t bytes)
{
	void	*target;

	target = malloc(bytes);
	if (!target)
		error_log("Error with the allocation");
	return (target);
}
