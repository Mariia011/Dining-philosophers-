/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:35 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/14 15:10:49 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

int	error_exit(char const *str)
{
	printf("%s", str);
	exit(EXIT_FAILURE);
}

long	ft_atol(const char *str)
{
	long	value;
	int		i;

	i = 0;
	value = 0;
	str = valid_input(str);
	while (str[i])
	{
		value += (value * 10) + (str[i] - '0');
		i++;
	}
	if (value > INT_MAX)
		return (error_exit("an INT_MAX was the LIMIT"));
	return (value);
}


char	*valid_input(const char *str)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	while (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		return (error_exit("Positive values only"));
	while (str[i])
	{
		if (str[i] < '0' && str[i] > '9')
			return (error_exit("The value doesn't contain a numerical value"));
		i++;
		len++;
	}
	if (len > 10)
		return (error_exit("Value is bigger than INT_MAX"));
	return (str + i);
}
