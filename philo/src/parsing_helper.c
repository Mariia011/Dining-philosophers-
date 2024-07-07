/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:35 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/07 21:55:34 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

long	ft_atolong(char *str)
{
	long	value;
	int		i;

	i = 0;
	value = 0;
	str = valid_input(str);
	
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
	while (str[i] && (str[i] == ' ' || str[i] == '\t' || str[i] == '\r' || str[i] == '\n'))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		error_exit("Positive values only");
	len = i;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			error_exit("The value contains a non-numerical value");
		i++;
	}
	return (str + len);
}
