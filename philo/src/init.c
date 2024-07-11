/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:08:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/11 17:22:47 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	__death(t_terms *table)
{
	free(table);
	error_exit("Bad argument values");
}

static void over_max_philo(void)
{
	printf("Maximum count of philos is %d\n", PHILO_MAX);
	exit(EXIT_FAILURE);
}

static void	philo_init(t_terms *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].id = i + 1;
		table->philos[i].is_full = false;
		table->philos[i].meal_counter = 0;
		table->philos[i].table = table;
		mutex_init(&table->forks[i].fork);
		mutex_init(&(table->philos[i].philo_mutex));
		table->forks[i].fork_id = i + 1;
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(table->philo_nbr + i - 1)
			% table->philo_nbr];
		table->philos[i].last_meal_time = 0;
		i++;
	}
}

void *one_philo_case(void *data)
{
	t_philo	*philo;
	philo = (t_philo *)data;

	wait_till_all_ready(philo->table);
	set_timeval(&philo->table->table_mutex, &philo->last_meal_time);
	increase_active_threads(&(philo->table->table_mutex), &(philo->table->active_threads));
	philo_status(TAKE_FORK, philo);
	printf("i'm here \n");
	while (!is_finished(philo->table))
		;
	return (NULL);
}

static void	data_init(t_terms *table)
{
	int	i;

	i = 0;
	table->the_end = false;
	table->if_ready = false;
	table->active_threads = 0;
	table->philos = safe_malloc(sizeof(t_philo) * table->philo_nbr);
	table->forks = safe_malloc(sizeof(t_fork) * table->philo_nbr);
	mutex_init(&table->table_mutex);
	mutex_init(&table->write_mutex);
	philo_init(table);
}

t_terms	*terms_parse(int argc, char **argv)
{
	t_terms	*table;

	table = safe_malloc(sizeof(t_terms));
	table->philo_nbr = ft_atolong(argv[PHILO_NUMBER]);
	if (table->philo_nbr > PHILO_MAX)
		over_max_philo();
	table->time_to_die = ft_atolong(argv[TIME_TO_DIE]) * MILLISECONDS;
	table->time_to_eat = ft_atolong(argv[TIME_TO_EAT]) * MILLISECONDS;
	table->time_to_sleep = ft_atolong(argv[TIME_TO_SLEEP]) * MILLISECONDS;
	if (table->time_to_die < (TIME_MIN) || table->time_to_eat < (TIME_MIN)
		|| table->time_to_sleep < (TIME_MIN))
	{
		printf("%ld %ld %ld", table->time_to_eat, table->time_to_sleep,
			table->time_to_die);
		error_exit("Use timestamps major than 60 ms");
	}
	if (argc == 6)
	{
		table->nbr_limit_meals = ft_atolong(argv[COUNT_OF_MEALS]);
		if (table->nbr_limit_meals < 0)
			__death(table);
	}
	else
		table->nbr_limit_meals = -1;
	data_init(table);
	return (table);
}