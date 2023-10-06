/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:37:49 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/06 17:07:35 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*thread_init(t_philo_stats *stats, int phil_nbr)
{
	int	i;

	i = 0;
	stats->time_ms = start_time();
	while (i < phil_nbr)
	{
		if (pthread_create(&(stats->all[i].thread_philo), NULL, thread_start, &(*stats).all[i]) != 0)
		{
			printf("Error creating Thread\n");
			exit(1);
		}
		i++;
	}
	check_phil(stats);
	i = 0;
	while (i < stats->nbr_phils)
	{
		pthread_join(stats->all[i].thread_philo, NULL);
		i++;
	}
	destroy_mutex(stats);
	return (NULL);
}

void	philo_init(t_philo **philo, t_philo_stats *stats)
{
	int i;

	i = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * stats->nbr_phils);
	stats->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * stats->nbr_phils);
	while (i < stats->nbr_phils)
	{
		memset((void *)&(*philo)[i], 0, sizeof(t_philo));
		pthread_mutex_init(&stats->forks[i], NULL);
		(*philo)[i].data = stats;
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].last_eat = start_time();
		i++;
	}
	return ;
}
