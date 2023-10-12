/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:55 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/12 16:21:53 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_philo(t_global_var *data, int *i)
{
	long long	tmp;

	while (*i < data->nbr_phils)
	{
		pthread_mutex_lock(&data->last_eat_lock);
		tmp = start_time() - data->all[*i].last_eat;
		pthread_mutex_unlock(&data->last_eat_lock);
		printf("%d\n", *i);
		if (tmp >= data->time_to_die)
		{
			pthread_mutex_lock(&data->philo_dead);
			data->end = 1;
			pthread_mutex_unlock(&data->philo_dead);
			put_msg(&data->all[*i], 'D');
			return (1);
		}
		*i = *i + 1;
	}
	return (0);
}

void	philo_monitor(t_global_var *data)
{
	int	i;
	
	while (data->nbr_phils != 1)
	{
		pthread_mutex_lock(&data->meals_nbr_lock);
		if (data->nbr_meals != -1
			&& data->all_ate == data->nbr_phils)
		{
			pthread_mutex_unlock(&data->meals_nbr_lock);
			printf("ALL PHILOSOPHERS ATE\n");		
			break ;
		}
		pthread_mutex_unlock(&data->meals_nbr_lock);
		i = 0;
		if (check_philo(data, &i))
			break ;
	}
	return ;
}

int	check_alive(t_global_var *data)
{
	pthread_mutex_lock(&data->philo_dead);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->philo_dead);
		return (1);
	}
	pthread_mutex_unlock(&data->philo_dead);
	return (0);
}
