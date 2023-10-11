/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:55 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/11 16:56:12 by rumachad         ###   ########.fr       */
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
		pthread_mutex_lock(&data->philo_dead);
		if (tmp >= data->time_to_die)
		{
			put_msg(&data->all[*i], 'D');
			data->end = 1;
			pthread_mutex_unlock(&data->philo_dead);
			return (1);
		}
		pthread_mutex_unlock(&data->philo_dead);
		*i = *i + 1;
	}
	return (0);
}

int	check_ate_all(t_global_var *data, int nbr_meals)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->meals_nbr_lock);
	while (i < data->nbr_phils && data->all[i].meals_nbr == nbr_meals)
		i++;
	pthread_mutex_unlock(&data->meals_nbr_lock);
	return (i);
}

void	philo_monitor(t_global_var *data)
{
	int	i;

	while (data->nbr_phils != 1)
	{
		i = 0;
		if (check_philo(data, &i))
			break ;
		if (data->nbr_meals > 0)
		{
			if (check_ate_all(data, data->nbr_meals)
				== data->nbr_phils)
				break ;
		}
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
