/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:27:38 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/20 13:33:28 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	grab_forks(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	sem_wait(philo->data->forks_sem);
	if (!check_alive(philo->data))
		put_msg(philo->philo_id, philo->data->time_ms, 'L');
	sem_wait(philo->data->forks_sem);
	if (!check_alive(philo->data))
		put_msg(philo->philo_id, philo->data->time_ms, 'R');
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (check_alive(philo->data))
	{
		sem_post(philo->data->forks_sem);
		sem_post(philo->data->forks_sem);
		return (1);
	}
	put_msg(philo->philo_id, philo->data->time_ms, 'E');
	sem_wait(philo->data->last_eat_sem);
	philo->last_eat = start_time();
	sem_post(philo->data->last_eat_sem);
	usleep(philo->data->time_to_eat * 1000);
	sem_wait(philo->data->meals_sem);
	philo->meals_nbr++;
	sem_post(philo->data->meals_sem);
	sem_post(philo->data->forks_sem);
	sem_post(philo->data->forks_sem);
	return (0);
}

int	philo_sleep_think(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	put_msg(philo->philo_id, philo->data->time_ms, 'S');
	usleep(philo->data->time_to_sleep * 1000);
	if (check_alive(philo->data))
		return (1);
	usleep(1000);
	put_msg(philo->philo_id, philo->data->time_ms, 'T');
	return (0);
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
		printf("Error\n");   //Change
	while (1)
	{
		if (grab_forks(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_full(philo))
			break ;
		if (philo_sleep_think(philo))
			break ;
	}
	pthread_join(philo->data->monitor, NULL);
	/* kill_dead(philo); */
}
