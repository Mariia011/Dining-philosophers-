/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/07 20:16:14 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_terms			*table;

	if (argc != 5 && argc != 6)
		return (error_exit("Wrong count of argc"));
		
	table = terms_parse(argc, argv);
	
	start_dinner(table);
	return (EXIT_SUCCESS);
}
