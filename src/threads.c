/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:13:51 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/11 16:44:00 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int join_threads(t_global_var *stats, int k, int flag)
{
	int	i;
	
	i = 0;
	if (flag == 1)
		printf("Error creating threads\n");
	while (i < k)
	{
		pthread_join(stats->all[i].thread_philo, NULL);
		i++;
	}
    return (0);
}

int	thread_init(t_global_var *stats)
{
	int	i;

	i = 0;
	stats->time_ms = start_time();
	while (i < stats->nbr_phils)
	{
		stats->all[i].last_eat = start_time();
		if (pthread_create(&(stats->all[i].thread_philo), NULL,
			thread_start, &(*stats).all[i]))
		{
			join_threads(stats, i, 1);
			destroy_mutex(stats, 3);
			return (1);
		}
		i++;
	}
	philo_monitor(stats);
	join_threads(stats, stats->nbr_phils, 0);
	destroy_mutex(stats, 3);
	return (0);
}
