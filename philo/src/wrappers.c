/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrappers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 21:16:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/02 14:12:27 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	*safe_malloc(size_t bytes)
{
	void	*target;

	target = malloc(bytes);
	if (!target)
		error_exit("Error with the allocation");
	return (target);
}
