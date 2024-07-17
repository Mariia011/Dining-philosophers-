/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 19:31:55 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:37:11 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

static int	error_log_bad(char const *str)
{
	printf("%s\n", str);
	printf("further behaiviour of program is undefined:)\n");
	return (-1);
}

int	error_log(char const *str)
{
	printf("%s\n", str);
	return (-1);
}

t_terms	*__death(t_terms *table)
{
	free(table);
	error_log("Bad argument values");
	return (NULL);
}
