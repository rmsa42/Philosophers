/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 14:27:38 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/18 16:43:31 by rumachad         ###   ########.fr       */
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
			put_msg(philo->philo_id, philo->data->time_ms, 'D');
			philo->data->end = 1;
			break ;
		}
	}
	
	return (NULL);
}

void    grab_forks(t_philo *philo)
{
    sem_wait(philo->data->sem1);
    put_msg(philo->philo_id, philo->data->time_ms, 'L');
    sem_wait(philo->data->sem1);
    put_msg(philo->philo_id, philo->data->time_ms, 'R');
}

void	philo_eat(t_philo *philo)
{
	put_msg(philo->philo_id, philo->data->time_ms, 'E');
	sem_wait(philo->data->last_eat_sem);
	philo->last_eat = start_time();
	sem_post(philo->data->last_eat_sem);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->sem1);
	sem_post(philo->data->sem1);
}

void	philo_sleep_think(t_philo *philo)
{
	put_msg(philo->philo_id, philo->data->time_ms, 'S');
	usleep(philo->data->time_to_sleep * 1000);
	put_msg(philo->philo_id, philo->data->time_ms, 'T');
}

void	process_routine(t_philo *philo)
{
	if (pthread_create(&(philo->data->monitor), NULL,
			&monitoring, philo))
		printf("Error\n");   //Change
	while (1)
	{
		grab_forks(philo);
		philo_eat(philo);
		philo_sleep_think(philo);
		break ;
	}
	pthread_join(philo->data->monitor, NULL);
	if (philo->data->end == 1)
	{
		printf("ab\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		exit(EXIT_SUCCESS);
	}
}