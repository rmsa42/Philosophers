/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:13:51 by rumachad          #+#    #+#             */
/*   Updated: 2024/08/09 14:36:06 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	join_threads(t_global_var *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_phils)
	{
		if (pthread_join(data->all[i].thread_philo, NULL))
			return (-1);
		i++;
	}
	return (0);
}

int	thread_init(t_global_var *data)
{
	int	i;

	i = 0;
	data->time_ms = start_time();
	while (i < data->nbr_phils)
	{
		data->all[i].last_eat = start_time();
		if (pthread_create(&(data->all[i].thread_philo), NULL,
				thread_start, &data->all[i]))
		{
			clean_program(data, 3);
			return (-1);
		}
		i++;
	}
	philo_monitor(data);
	if (join_threads(data) == -1)
		printf("Error Joining Threads\n");
	clean_program(data, 3);
	return (0);
}
