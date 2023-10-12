/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:37:49 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/12 16:10:34 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	stats_init(t_global_var *stats, char **av)
{
	stats->nbr_phils = ft_atoi(av[1]);
	stats->time_to_die = ft_atoi(av[2]);
	stats->time_to_eat = ft_atoi(av[3]);
	stats->time_to_sleep = ft_atoi(av[4]);
	stats->end = 0;
	if (av[5])
		stats->nbr_meals = ft_atoi(av[5]);
	else
		stats->nbr_meals = -1;
	if (stats->nbr_phils == 0 || stats->time_to_die == 0
		|| stats->time_to_eat == 0 || stats->time_to_sleep == 0
		|| stats->nbr_meals == 0)
	{
		printf("Invalid Arguments\n");
		return (1);
	}
	return (0);
}

int	forks_init(t_global_var *stats)
{
	int	i;

	i = 0;
	while (i < stats->nbr_phils)
	{
		if (pthread_mutex_init(&stats->forks[i], NULL))
		{
			destroy_mutex(stats, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	mutex_init(t_global_var *stats)
{
	if (forks_init(stats))
		return (1);
	if (pthread_mutex_init(&stats->last_eat_lock, NULL))
	{
		destroy_mutex(stats, 0);
		return (1);
	}
	if (pthread_mutex_init(&stats->meals_nbr_lock, NULL))
	{
		destroy_mutex(stats, 1);
		return (1);
	}
	if (pthread_mutex_init(&stats->philo_dead, NULL))
	{
		destroy_mutex(stats, 2);
		return (1);
	}
	return (0);
}

int	philo_init(t_philo **philo, t_global_var *stats)
{
	int	i;

	i = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * stats->nbr_phils);
	if (*philo == NULL)
		return (1);
	stats->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * stats->nbr_phils);
	if (stats->forks == NULL)
		return (1);
	if (mutex_init(stats))
		return (1);
	while (i < stats->nbr_phils)
	{
		memset((void *)&(*philo)[i], 0, sizeof(t_philo));
		(*philo)[i].data = stats;
		(*philo)[i].philo_id = i + 1;
		i++;
	}
	stats->all = *philo;
	stats->all_ate = 0;
	return (0);
}
