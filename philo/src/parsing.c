/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:35 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/25 16:49:33 by marikhac         ###   ########.fr       */
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

const char	*valid_input(const char *str)
{
	int	len;
	int	i;

	i = 0;
	while ((str[i] >= 9) && (str[i] <= 13 || str[i] == 32))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		error_exit("Positive values only");
	len = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error_exit("The value doesn't contain a numerical value");
		i++;
	}
	// printf("%s", str + len);
	return (str + len);
}
