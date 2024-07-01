/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 14:32:41 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 20:57:43 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"


static void	wait_till_all_ready(t_terms *table)
{
	while(false == table->if_ready)
		;
	if (gettimeofday(table->start_simulation))

}

