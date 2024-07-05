/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/05 19:37:44 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_terms			the_table;

	if (argc != 5 && argc != 6)
		return (error_exit("Wrong count of argc"));
	terms_parse(&the_table, argc, argv);
	start_dinner(&the_table);
	// end_dinner(&the_table);
	return (EXIT_SUCCESS);
}
