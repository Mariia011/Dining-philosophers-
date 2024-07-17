/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamirkha <aamirkha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/17 18:15:52 by aamirkha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	main(int argc, char **argv)
{
	t_terms	*table;

	if (argc != 5 && argc != 6)
		return (error_log("Wrong count of argc"));
	table = terms_parse(argc, argv);
	if (NULL == table)
		return (EXIT_FAILURE);
	start_dinner(table);
	table_destroy(&table);
	return (EXIT_SUCCESS);
}


void __attribute__((destructor)) foo()
{
	system("leaks philo");
}
