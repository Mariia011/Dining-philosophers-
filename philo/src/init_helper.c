/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:35 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 17:39:17 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

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
		return (error_exit("an INT_MAX was the LIMIT"));
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
	{
		error_exit("Positive values only");
		return (NULL);
	}
	len = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			error_exit("The value contains a non-numerical value");
			return (NULL);
		}
		i++;
	}
	return (str + len);
}
