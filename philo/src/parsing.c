/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:08:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/01 20:44:07 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

void	philo_to_thread(t_terms *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		safe_thread_handle(&table->philos[i].thread, start_dinner, table->philos
			+ i, CREATE);
		printf("thread of philo %d has been created\n", i + 1);
		i++;
	}
	shift_flag(&table->mtx, &table->if_ready, true);
	end_dinner(table);
}

static void	philo_init(t_terms *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_full = false;
		table->philos[i].meals_counter = 0;
		table->philos[i].table = table;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(table->philo_nbr + i - 1)
			% table->philo_nbr];
		i++;
	}
	philo_to_thread(table);
}

static void	data_init(t_terms *table)
{
	int	i;

	i = 0;
	table->end = false;
	table->if_ready = false;
	table->active_threads = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	while (i < table->philo_nbr)
	{
		safe_mutex_handle(&table->forks[i].fork, INIT);
		table->forks[i].fork_id = i + 1;
		i++;
	}
	safe_mutex_handle(&table->table_mutex, INIT);
	safe_mutex_handle(&table->write_mutex, INIT);
	philo_init(table);
}

void	terms_parse(t_terms *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[PHILO_NUMBER]);
	if (table->philo_nbr > PHILO_MAX)
	{
		printf("Maximum count of philos is %d\n", PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	table->time_to_die = ft_atol(argv[TIME_TO_DIE]) * MILLISECONDS;
	table->time_to_eat = ft_atol(argv[TIME_TO_EAT]) * MILLISECONDS;
	table->time_to_sleep = ft_atol(argv[TIME_TO_SLEEP]) * MILLISECONDS;
	if (table->time_to_die < (TIME_MIN * MILLISECONDS)
		|| table->time_to_eat < (TIME_MIN * MILLISECONDS)
		|| table->time_to_sleep < (TIME_MIN * MILLISECONDS))
	{
		printf("%ld %ld %ld", table->time_to_eat, table->time_to_sleep,
			table->time_to_die);
		error_exit("Use timestamps major than 60 ms");
	}
	if (argv[COUNT_OF_MEALS])
		table->nbr_limit_meals = ft_atol(argv[COUNT_OF_MEALS]);
	else
		table->nbr_limit_meals = -1;
	data_init(table);
}
