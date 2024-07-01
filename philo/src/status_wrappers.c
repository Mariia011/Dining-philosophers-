/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status_wrappers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:01:03 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 16:14:11 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static void __eat(t_philo *philo, t_time now)
{
	printf(PURPLE);
	printf("%ld %i is eating", now, philo->id);
	printf(RESET);
}

static void __die(t_philo *philo, t_time now)
{
	printf(YELLOW);
	printf("%ld %i is dead", now, philo->id);
	printf(RESET);
}

void	philo_status(t_philo *philo, t_code philo_status)
{
	t_time now;

	__lock(&(philo->table->write_mutex));
	if(is_finished(&philo->table)) return ;
	now = get_time(MILLISECONDS) - philo->start_simulation ;
 	if (philo_status == TAKE_FORK)
		printf("%ld philo %d has taken a fork", now, philo->id);
	else if (EAT == opcode)
		__eat(philo, now);
	else if (SLEEP == opcode)
		printf("%ld %ld is sleeping\n", now, philo->id);
	else if (THINK == opcode)
		printf("%i %ld is thinking\n", now, philo->id);
	else if (DIE == opcode)
		__die(philo, now);
	__unlock(&(philo->table->write_mutex));
}
