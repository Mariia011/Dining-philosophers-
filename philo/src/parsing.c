/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:08:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/07/04 14:27:41 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

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
		table->philos[i].right_fork = &table->forks[i];
		table->philos[i].left_fork = &table->forks[(table->philo_nbr + i - 1) % table->philo_nbr];
		i++;
	}
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
	while (i < table->philo_nbr)
	{
		mutex_init(&table->forks[i].fork);
		table->forks[i].fork_id = i + 1;
		i++;
	}
	mutex_init(&table->table_mutex);
	mutex_init(&table->write_mutex);
	philo_init(table);
}

void	terms_parse(t_terms *table, int argc, char **argv)
{
	table->philo_nbr = ft_atolong(argv[PHILO_NUMBER]);
	table->philo_nbr = 3;
	if (table->philo_nbr > PHILO_MAX)
	{
		printf("Maximum count of philos is %d\n", PHILO_MAX);
		exit(EXIT_FAILURE);
	}
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
		table->nbr_limit_meals = ft_atolong(argv[COUNT_OF_MEALS]);
	else
		table->nbr_limit_meals = -1;
	data_init(table);
}
