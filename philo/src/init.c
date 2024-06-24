/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:08:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/24 16:37:10 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"


void *start_dinner(t_terms *table)
{
	printf("hello philo nbr %d", table->philo_nbr);
	return NULL;
}

void end_dinner(t_terms *table)
{
	int i = 0;
	while(i < table->philo_nbr)
	{
		free(&table->forks[i]);
		// table->forks[i] = NULL;
		free(&table->philos[i]);
		// table->philos[i] = NULL;
		i++;
	}
}

static void philo_to_thread(t_terms *table)
{
	int i = 0;
	while(i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread, &start_dinner, &table, CREATE);
		i++;
		printf("thread of philo %d has been created", i);
	}
	end_dinner(table);
}

static void philo_init(t_terms *table)
{
	int i = 0;
	while(i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[i + 1 % table->philo_nbr] ;
		i++;
	}
	philo_to_thread(table->philos);
}

static void	data_init(t_terms *table)
{
	int	i;

	i = 0;
	table->the_end = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i + 1;
		i++;
	}
	philo_init(table);
}

void	terms_parse(t_terms *the_table, char **argv)
{
	the_table->philo_nbr = ft_atol(argv[1]);
	if (the_table->philo_nbr > PHILO_MAX)
	{
		printf("Maximum count of philos is %d\n", PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	the_table->time_to_die = ft_atol(argv[2]) * MILLISECONDS;
	the_table->time_to_eat = ft_atol(argv[3]) * MILLISECONDS;
	the_table->time_to_sleep = ft_atol(argv[4]) * MILLISECONDS;
	if (the_table->time_to_die < (60 * MILLISECONDS) || the_table->time_to_eat < (60
			* MILLISECONDS) || the_table->time_to_sleep < (60 * MILLISECONDS))
		error_exit("Use timestamps major than 60 ms");
	if (argv[5])
		the_table->nbr_limit_meals = ft_atol(argv[5]);
	else
		the_table->nbr_limit_meals = -1;
	data_init(the_table);
}
