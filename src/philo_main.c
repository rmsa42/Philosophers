/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/05 18:06:18 by rui              ###   ########.fr       */
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

void	*thread_start(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		if (check_phil(philo) == 1)
			break ;
		if (philo->philo_id % 2 == 1)
		{
			pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
			put_msg(philo, 'L');
			pthread_mutex_lock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
			put_msg(philo, 'R');
		}
		else
		{
			usleep(100);
			pthread_mutex_lock(&(philo->data->forks[philo->philo_id - 1]));
			put_msg(philo, 'L');
			pthread_mutex_lock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
			put_msg(philo, 'R');
		}
		put_msg(philo, 'E');
		usleep(philo->data->time_to_eat * 1000);
		philo->last_eat = start_time();
		philo->meals_nbr++;
		put_msg(philo, 'S');
		usleep(philo->data->time_to_sleep * 1000);
		put_msg(philo, 'T');
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_id - 1]));
		pthread_mutex_unlock(&(philo->data->forks[philo->philo_id % philo->data->nbr_phils]));
	}
	return (NULL);
}

void	*thread_init(t_philo_stats *stats, int phil_nbr)
{
	int	i;

	i = 0;
	stats->time_ms = start_time();
	while (i < phil_nbr)
	{
		if (pthread_create(&((*stats).all[i].thread_philo), NULL, thread_start, &(*stats).all[i]) != 0)
		{
			printf("Error creating Thread\n");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < phil_nbr)
	{
		if (pthread_join((*stats).all[i].thread_philo, NULL) != 0)
		{
			printf("Error creating Thread\n");
			exit(1);
		}
		i++;
	}
	return (NULL);
}

void	philo_init(t_philo **philo, t_philo_stats *stats)
{
	int i;

	i = 0;
	*philo = (t_philo *)malloc(sizeof(t_philo) * stats->nbr_phils);
	stats->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * stats->nbr_phils);
	while (i < stats->nbr_phils)
	{
		memset((void *)&(*philo)[i], 0, sizeof(t_philo));
		pthread_mutex_init(&stats->forks[i], NULL);
		(*philo)[i].data = stats;
		(*philo)[i].philo_id = i + 1;
		i++;
	}
	return ;
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
	philo_init(&philo, &stats);
	stats.all = philo;
	thread_init(&stats, stats.nbr_phils);
	return (0);
}
