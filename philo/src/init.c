/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:08:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/25 21:22:15 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

void	wait_till_all_ready(t_terms *table)
{
	while(false == table->if_ready);
}


void *start_dinner(void *data)
{
	t_philo* philo = (t_philo*)data;
	int i = 0;

	wait_till_all_ready(philos);
	while(i < philo_nbr)
	{
		//choto
	}
	return NULL;
}

void end_dinner(t_terms *table)
{
	int i = 0;
	while(i < table->philo_nbr)
	{
		free(&table->forks[i]);
		free(&table->philos[i]);
		i++;
	}
}

static void philo_to_thread(t_terms *table)
{
	int i = 0;
	while(i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread, start_dinner, table->philos + i, CREATE);
		printf("thread of philo %d has been created\n", i + 1);
		i++;
	}

	shift_flag(&table->mtx, &table->if_ready, true);
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
		table->philos[i].left_fork = &table->forks[(table->philo_nbr + i - 1) % table->philo_nbr];
		i++;
	}
	philo_to_thread(table);
}

static void	data_init(t_terms *table)
{
	int	i;

	i = 0;
	table->the_end = false;
	table->if_eady = false;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i + 1;
		i++;
	}
	safe_mutex_handle(&table->mtx, INIT);
	philo_init(table);
}

void	terms_parse(t_terms *the_table, char **argv)
{
	the_table->philo_nbr = ft_atol(argv[PHILO_NUMBER]);
	if (the_table->philo_nbr > PHILO_MAX)
	{
		printf("Maximum count of philos is %d\n", PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	the_table->time_to_die = ft_atol(argv[TIME_TO_DIE]) * MILLISECONDS;
	the_table->time_to_eat = ft_atol(argv[TIME_TO_EAT]) * MILLISECONDS;
	the_table->time_to_sleep = ft_atol(argv[TIME_TO_SLEEP]) * MILLISECONDS;
	if (the_table->time_to_die < (TIME_MIN * MILLISECONDS) || the_table->time_to_eat < (TIME_MIN * MILLISECONDS)
		|| the_table->time_to_sleep < (TIME_MIN * MILLISECONDS))
		{
		printf("%ld %ld %ld", the_table->time_to_eat, the_table->time_to_sleep, the_table->time_to_die);
		error_exit("Use timestamps major than 60 ms");
		}
	if (argv[COUNT_OF_MEALS])
		the_table->nbr_limit_meals = ft_atol(argv[COUNT_OF_MEALS]);
	else
		the_table->nbr_limit_meals = -1;
	data_init(the_table);
}
