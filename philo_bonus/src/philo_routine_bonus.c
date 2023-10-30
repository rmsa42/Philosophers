/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:27:38 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/30 15:36:54 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	grab_forks(t_philo *philo)
{
	sem_wait(philo->data->forks_sem);
	put_msg(philo, 'L');
	sem_wait(philo->data->forks_sem);
	put_msg(philo, 'R');
}

void	philo_eat(t_philo *philo)
{
	put_msg(philo, 'E');
	sem_wait(philo->data->last_eat_sem);
	philo->last_eat = start_time();
	sem_post(philo->data->last_eat_sem);
	usleep(philo->data->time_to_eat * 1000);
	sem_wait(philo->data->meals_sem);
	philo->meals_nbr++;
	sem_post(philo->data->meals_sem);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
}

void	philo_sleep_think(t_philo *philo)
{
	put_msg(philo, 'S');
	usleep(philo->data->time_to_sleep * 1000);
	put_msg(philo, 'T');
}

int	philo_full(t_philo *philo)
{
	sem_wait(philo->data->meals_sem);
	if (philo->meals_nbr == philo->data->nbr_meals)
	{
		sem_post(philo->data->meals_sem);
		return (1);
	}
	sem_post(philo->data->meals_sem);
	return (0);
}

void	process_routine(t_philo *philo)
{
	if (pthread_create(&(philo->data->monitor), NULL,
			&monitoring, philo))
	{
		printf("Error creatig thread\n");
		exit(EXIT_FAILURE);
	}
	if (pthread_detach(philo->data->monitor))
	{
		printf("Error in pthread_detach\n");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (philo->philo_id % 2)
			usleep(4000);
		grab_forks(philo);
		philo_eat(philo);
		if (philo_full(philo))
			exit(EXIT_SUCCESS);
		philo_sleep_think(philo);
	}
}
