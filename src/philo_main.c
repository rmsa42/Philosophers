/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/09 18:31:30 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_alive(t_philo_stats *data)
{
	pthread_mutex_lock(&data->philo_dead);
	if (data->end == 1)
	{
		pthread_mutex_unlock(&data->philo_dead);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->philo_dead);
	return (0);
}

int	philo_take_forks(t_philo *philo)
{
	if (check_alive(philo->data))
		return (1);
	pthread_mutex_lock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
	put_msg(philo, 'R');
	pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
	put_msg(philo, 'L');
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (check_alive(philo->data))
	{
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
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
	pthread_mutex_unlock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
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

void	*thread_start(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->data->end && philo->data->nbr_meals != philo->meals_nbr)
	{	
		if (philo->philo_id % 2)
			usleep(1000);
		if (philo_take_forks(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_think_sleep(philo))
			break ;
	}
	return (NULL);
}

int main(int argc, char **av)
{
	t_philo	*philo;
	t_philo_stats stats;

	if (argc == 5 || argc == 6)
	{	
		philo = NULL;
		stats.nbr_phils = ft_atoi(av[1]);
		stats.time_to_die = ft_atoi(av[2]);
		stats.time_to_eat = ft_atoi(av[3]);
		stats.time_to_sleep = ft_atoi(av[4]);
		if (av[5])
			stats.nbr_meals = ft_atoi(av[5]);
		stats.end = 0;
		philo_init(&philo, &stats);
		stats.all = philo;
		thread_init(&stats, stats.nbr_phils);
	}
	return (0);
}
