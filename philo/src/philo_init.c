/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:37:49 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/16 16:39:01 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	data_init(t_global_var *data, char **av)
{
	data->nbr_phils = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->end = 0;
	if (av[5])
		data->nbr_meals = ft_atoi(av[5]);
	else
		data->nbr_meals = -1;
	if (data->nbr_phils == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| data->nbr_meals == 0)
	{
		printf("Invalid Arguments\n");
		return (-1);
	}
	return (0);
}

int	forks_init(t_global_var *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_phils)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			clean_program(data, 0);
			return (1);
		}
		i++;
	}
	return (0);
}

int	mutex_init(t_global_var *data)
{
	if (forks_init(data))
		return (-1);
	if (pthread_mutex_init(&data->last_eat_lock, NULL))
	{
		clean_program(data, 0);
		return (-1);
	}
	if (pthread_mutex_init(&data->meals_nbr_lock, NULL))
	{
		clean_program(data, 1);
		return (-1);
	}
	if (pthread_mutex_init(&data->philo_dead, NULL))
	{
		clean_program(data, 2);
		return (-1);
	}
	return (0);
}

int	philo_init(t_philo **philo, t_global_var *data)
{
	int	i;

	i = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * data->nbr_phils);
	if (*philo == NULL)
		return (-1);
	data->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * data->nbr_phils);
	if (data->forks == NULL)
		return (-1);
	while (i < data->nbr_phils)
	{
		memset((void *)&(*philo)[i], 0, sizeof(t_philo));
		(*philo)[i].data = data;
		(*philo)[i].philo_id = i + 1;
		i++;
	}
	data->all = *philo;
	return (0);
}
