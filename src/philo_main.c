/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/09/29 17:19:44 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int k = 1;

void	*thread_start(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data.forks[philo->philo_id]);
	printf("Phil %d\n", philo->philo_id);
	pthread_mutex_unlock(&philo->data.forks[philo->philo_id]);
	return (NULL);
}

void	*thread_init(t_philo_stats stats, int phil_nbr)
{
	int	i;

	i = 0;
	while (i < phil_nbr)
	{
		stats.all[i].time_alive = start_time();
		if (pthread_create(&(stats.all[i].thread_philo), NULL, thread_start, &stats.all[i]) != 0)
		{
			printf("Error creating Thread\n");
			exit(1);
		}
		i++;
	}
	/* check_phil(&stats); */
	i = 0;
	while (i < phil_nbr)
	{
		if (pthread_join(stats.all[i].thread_philo, NULL) != 0)
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
	*philo = malloc(sizeof(t_philo) * stats->nbr_phils);
	while (i < stats->nbr_phils)
	{
		memset((void *)&(*philo)[i], 0, sizeof(t_philo));
		pthread_mutex_init(&stats->forks[i], NULL);
		(*philo)[i].philo_id = i + 1;
		i++;
	}
	return ;
}

int main(int argc, char **av)
{
	t_philo	*philo;
	t_philo_stats stats;

	if (argc != 3)
		return (0);
	philo = NULL;
	stats.nbr_phils = ft_atoi(av[1]);
	stats.time_to_die = ft_atoi(av[2]);
	stats.forks = malloc(sizeof(pthread_mutex_t) * stats.nbr_phils);
	philo_init(&philo, &stats);
	stats.all = philo;
	thread_init(stats, stats.nbr_phils);
	return (0);
}
