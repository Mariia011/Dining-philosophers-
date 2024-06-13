/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:40:32 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/13 20:50:56 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

void *create(void* data)
{
	for(unsigned long i = 0; i < 100; i++)
	{
		pthread_mutex_lock(&mutex);
		count++;
		usleep(1000);
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

void table_init(t_table *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	if(table->philo_nbr > PHILO_MAX)
	{
		printf("Max philos are %d\n",PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	table->time_to_die = ft_atol(av[2]) * MILLISECONDS;
	table->time_to_eat = ft_atol(av[3]) * MILLISECONDS;
	table->time_to_sleep = ft_atol(av[4]) * MILLISECONDS;
	if(table->time_to_die < (60 * MILLISECONDS)
		|| table->time_to_eat < (60 * MILLISECONDS)
		|| table->time_to_sleep < (60 * MILLISECONDS))
	error_exit("Use timestamps major than 60 ms");
	if(av[5])
		table->nbr_limit_meals = ft_atol(av[5]);
	else
		table->nbr_limit_meals = -1;
}




static void data_init(t_table *table)
{

}

void data_init(t_table *table)
{
	int i;

	i = 0;
	table->end_simulation = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while(i < table->philo_nbr)
}

int main(int argc, char **argv)
{
	t_table the_table;
	if(argc != 5 || argc != 6)
		return(err_exit("Wrong count of argc"));
	table_init(&the_table, argv);
	philo_init(&the_table);
	pthread_mutex_init(&mutex, NULL);
	pthread_t philosopher[PHILOS];

	for (int i = 1; i <= PHILOS; i++)
	{
		if(pthread_create(philosopher + i, NULL, &create, &i) != 0)
			return 0;
		printf("philo number %d is created\n", i);
	}
	for (int i = 1; i <= PHILOS; i++)
	{
		if(pthread_join(philosopher[i], NULL) != 0)
			return 0;
		printf("philo %d died\n", i);
	}
	pthread_mutex_destroy(&mutex);
	printf("the count is %u \n", count);
	return 0;
}
