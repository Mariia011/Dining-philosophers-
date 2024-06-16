/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marikhac <marikhac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 15:08:39 by marikhac          #+#    #+#             */
/*   Updated: 2024/06/16 19:42:16 by marikhac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "/Users/marikhac/Desktop/philo/philo/includes/philosophers.h"

static void assign_forks(t_terms *table, t_fork *forks,int position)
{
	int philo_nbr = table->philo_nbr;
	int i = 0;
	while(i < philo_nbr)
	{
		table->philos[i].right_fork = &forks[position];
		table->philos[i].left_fork = &forks[position + 1] % philo_nbr;
		i++;
	}
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
		i++;
	}
}

void	data_init(t_terms *table)
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
}

void	terms_init(t_terms *table, char **argv)
{
	table->philo_nbr = ft_atol(argv[1]);
	if (table->philo_nbr > PHILO_MAX)
	{
		printf("Max philos are %d\n", PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	table->time_to_die = ft_atol(argv[2]) * MILLISECONDS;
	table->time_to_eat = ft_atol(argv[3]) * MILLISECONDS;
	table->time_to_sleep = ft_atol(argv[4]) * MILLISECONDS;
	if (table->time_to_die < (60 * MILLISECONDS) || table->time_to_eat < (60
			* MILLISECONDS) || table->time_to_sleep < (60 * MILLISECONDS))
		error_exit("Use timestamps major than 60 ms");
	if (argv[5])
		table->nbr_limit_meals = ft_atol(argv[5]);
	else
		table->nbr_limit_meals = -1;
}
