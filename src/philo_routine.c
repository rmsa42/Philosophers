/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:40:32 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/11 17:02:19 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_take_forks(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	if (!(philo->philo_id % 2))
	{
		pthread_mutex_lock(&(philo->data->forks
			[philo->philo_id % philo->data->nbr_phils]));
		if (!check_alive(philo->data))
			put_msg(philo, 'R');
		pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
		if (!check_alive(philo->data))
			put_msg(philo, 'L');
	}
	else
	{
		pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
		if (!check_alive(philo->data))
			put_msg(philo, 'L');
		pthread_mutex_lock(&(philo->data->forks
			[philo->philo_id % philo->data->nbr_phils]));
		if (!check_alive(philo->data))
			put_msg(philo, 'R');
	}
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (check_alive(philo->data))
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
		pthread_mutex_unlock(&(philo->data->forks
			[philo->philo_id % philo->data->nbr_phils]));
		return (1);
	}
	put_msg(philo, 'E');
	pthread_mutex_lock(&philo->data->last_eat_lock);
	philo->last_eat = start_time();
	pthread_mutex_unlock(&philo->data->last_eat_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_lock(&philo->data->meals_nbr_lock);
	philo->meals_nbr++;
	pthread_mutex_unlock(&philo->data->meals_nbr_lock);
	pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
	pthread_mutex_unlock(&(philo->data->forks
		[philo->philo_id % philo->data->nbr_phils]));
	if (philo->meals_nbr == philo->data->nbr_meals)
		return (1);
	return (0);
}

int	philo_think_sleep(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	put_msg(philo, 'S');
	if (check_alive(philo->data))
		return (1);
	usleep(philo->data->time_to_sleep * 1000);
	if (check_alive(philo->data))
		return (1);
	put_msg(philo, 'T');
	return (0);
}

int	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[0]);
	put_msg(philo, 'L');
	usleep(philo->data->time_to_die * 1000);
	put_msg(philo, 'D');
	pthread_mutex_unlock(&philo->data->forks[0]);
	return (1);
}

void	*thread_start(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->philo_id % 2)
		usleep(4000);
	while (philo->data->end == 0)
	{
		if (philo->data->nbr_phils == 1)
		{
			if (one_philo(philo))
				break ;
		}
		else
		{
			if (philo_take_forks(philo))
				break ;
			if (philo_eat(philo))
				break ;
			if (philo_think_sleep(philo))
				break ;				
		}
	}
	return (NULL);
}
