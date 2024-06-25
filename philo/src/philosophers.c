/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/25 15:48:12 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_terms			the_table;

	if (argc != 5 && argc != 6)
		return (error_exit("Wrong count of argc"));
	terms_parse(&the_table, argv);
	// start_dinner(&the_table);
	end_dinner(&the_table);
	return (EXIT_SUCCESS);
}

// write the init for  for threads, for mutex, for table);
