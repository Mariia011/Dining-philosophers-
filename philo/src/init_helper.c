/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:35 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:41:36 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static char	*error_log_wrap(char *msg)
{
	error_log(msg);
	return (NULL);
}

void	calculate_think(t_philo *philo)
{
	long	val;

	val = philo->table->time_to_eat * 2 - philo->table->time_to_sleep;
	if (val > 0)
		ft_usleep(val / 2, philo->table);
}

long	ft_atolong(char *str)
{
	long	value;
	int		i;

	i = 0;
	value = 0;
	str = valid_input(str);
	if (!str)
		return (-1);
	while (str[i])
	{
		value = (value * 10) + (str[i] - '0');
		i++;
	}
	if (value > INT_MAX || value < 0)
		return (error_log("an INT_MAX was the LIMIT"));
	return (value);
}

char	*valid_input(char *str)
{
	int	len;
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
			|| str[i] == '\n'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (error_log_wrap("Positive values only"));
	len = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (error_log_wrap("The value contains a non-numerical value"));
		i++;
	}
	return (str + len);
}

void	*one_philo_case(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_till_all_ready(philo->table);
	set_timeval(&philo->table->table_mutex, &philo->last_meal_time);
	increase_active_threads(&(philo->table->table_mutex),
		&(philo->table->active_threads));
	philo_status(TAKE_FORK, philo);
	while (!is_finished(philo->table))
		;
	return (NULL);
}
