/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/16 20:18:22 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

// void	*create(void *data)
// {
// 	for (unsigned long i = 0; i < 100; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		pthread_mutex_unlock(&mutex);
// 	}
// 	return (NULL);
// }

int	main(int argc, char **argv)
{
	t_terms		the_table;
	pthread_t	philosopher[PHILOS];
	pthread_mutex_t mutex;

	if (argc != 5 || argc != 6)
		return (err_exit("Wrong count of argc"));
	terms_init(&the_table, argv);
	philo_init(&the_table);
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}


//write the init till the end (function for forks, for philos, for threads, for mutex, for table);
