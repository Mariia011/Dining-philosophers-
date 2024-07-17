/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:35 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:15:52 by aamirkha         ###   ########.fr       */
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
	{
		error_log("Positive values only");
		return (NULL);
	}
	len = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			error_log("The value contains a non-numerical value");
			return (NULL);
		}
		i++;
	}
	return (str + len);
}
