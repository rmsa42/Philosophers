/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 11:03:42 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/20 15:40:10 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	*monitoring(void *arg)
{
	int	tmp;
	t_philo	*philo;
	
	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->last_eat_sem);
		tmp = start_time() - philo->last_eat;
		sem_post(philo->data->last_eat_sem);
		if (tmp >= philo->data->time_to_die)
		{
			put_msg(philo, 'D');
			exit(EXIT_FAILURE);
		}
		sem_wait(philo->data->meals_sem);
		if (philo->meals_nbr == philo->data->nbr_meals)
		{
			sem_post(philo->data->meals_sem);
			break ;
		}
		sem_post(philo->data->meals_sem);
	}
	return (NULL);
}

int	check_alive(t_global_var *data)
{
	sem_wait(data->death_sem);
	if (data->end == 1)
	{
		sem_post(data->death_sem);
		return (1);
	}
	sem_post(data->death_sem);
	return (0);
}

void	kill_dead(t_philo *philo)
{
	sem_wait(philo->data->death_sem);
	if (philo->data->end == 1)
	{
		exit(EXIT_FAILURE);
	}
	else
	{
		sem_post(philo->data->death_sem);
		exit(EXIT_SUCCESS);
	}
}
