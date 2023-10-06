/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/06 17:10:26 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	put_msg(t_philo *philo, char c)
{
	long long	tmp;

	tmp = start_time() - philo->data->time_ms;
	if (c == 'S')
		printf("[%lld] Philo %d is sleeping\n", tmp, philo->philo_id);
	else if (c == 'T')
		printf("[%lld] Philo %d is thinking\n", tmp, philo->philo_id);
	else if (c == 'E')
		printf("[%lld] Philo %d is eating. Forks: %d %d\n", tmp, philo->philo_id,
				philo->philo_id - 1 , philo->philo_id % philo->data->nbr_phils);
	else if (c == 'L')
		printf("[%lld] Philo %d has taken a fork: %d\n", tmp, philo->philo_id,
				philo->philo_id - 1);
	else if (c == 'R')
		printf("[%lld] Philo %d has taken a fork: %d\n", tmp, philo->philo_id,
				philo->philo_id % philo->data->nbr_phils);
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
	put_msg(philo, 'L');
	pthread_mutex_lock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
	put_msg(philo, 'R');
	put_msg(philo, 'E');
	philo->last_eat = start_time();
	usleep(philo->data->time_to_eat * 1000);
	philo->meals_nbr++;
	pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
	pthread_mutex_unlock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
}

void	*thread_start(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!philo->data->end && philo->data->nbr_meals != philo->meals_nbr)
	{
		if (philo->philo_id % 2)
			usleep(500);
		philo_eat(philo);
		put_msg(philo, 'S');
		usleep(philo->data->time_to_sleep * 1000);
		put_msg(philo, 'T');
	}
	return (NULL);
}

int main(int argc, char **av)
{
	t_philo	*philo;
	t_philo_stats stats;

	if (argc != 6)
		return (0);
	philo = NULL;
	stats.nbr_phils = ft_atoi(av[1]);
	stats.time_to_die = ft_atoi(av[2]);
	stats.time_to_eat = ft_atoi(av[3]);
	stats.time_to_sleep = ft_atoi(av[4]);
	stats.nbr_meals = ft_atoi(av[5]);
	stats.end = 0;
	philo_init(&philo, &stats);
	stats.all = philo;
	thread_init(&stats, stats.nbr_phils);
	return (0);
}
