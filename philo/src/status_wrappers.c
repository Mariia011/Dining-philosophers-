/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_wrappers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:01:03 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/05 18:02:20 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void	__eat(t_philo *philo, t_time now)
{
	printf(PURPLE);
	printf("%ld %i is eating", now, philo->id);
	printf(RESET);
}

static void	__die(t_philo *philo, t_time now)
{
	printf(YELLOW);
	printf("%ld %i is dead", now, philo->id);
	printf(RESET);
}

void	philo_status(t_code philo_status, t_philo *philo)
{
	t_time	now;

	__lock(&(philo->table->write_mutex));
	if (is_finished(philo->table))
		return ;
	now = get_time(MILLISECONDS) - philo->table->start_simulation;
	if (philo_status == TAKE_FORK)
		printf("%ld philo %d has taken a fork", now, philo->id);
	else if (EAT == philo_status)
		__eat(philo, now);
	else if (SLEEP == philo_status)
		printf("%ld %d is sleeping\n", now, philo->id);
	else if (THINK == philo_status)
		printf("%ld %d is thinking\n", now, philo->id);
	else if (DIE == philo_status)
		__die(philo, now);
	__unlock(&(philo->table->write_mutex));
}
