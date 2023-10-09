/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:55 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/09 16:11:42 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_phil(t_philo_stats *data)
{
	long long	tmp;
	int			i;
	int			count;

	count = 0;
	while (!data->end && count != data->nbr_phils)
	{
		i = 0;
		while (i < data->nbr_phils && !data->end)
		{
			pthread_mutex_lock(&data->last_eat_lock);
			tmp = start_time() - data->all[i].last_eat;
			pthread_mutex_unlock(&data->last_eat_lock);
			if (tmp >= data->time_to_die)
			{
				put_msg(&data->all[i], 'D');
				pthread_mutex_lock(&data->philo_dead);
				data->end = 1;
				pthread_mutex_unlock(&data->philo_dead);
			}
			pthread_mutex_lock(&data->meals_nbr_lock);
			if (data->all[i].meals_nbr == data->nbr_meals)
				count++;
			pthread_mutex_unlock(&data->meals_nbr_lock);
			i++;
		}
	}
	return ;
}
 