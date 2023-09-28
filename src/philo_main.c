/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/09/28 16:50:24 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*thread_start(void *arg)
{
	t_philo *philos;

	philos = (t_philo *)arg;
	while (1)
	{
		
	}
	return (NULL);
}

void	*philos_init(t_philo_stats stats, int phil_nbr)
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
		stats.all[i].philo_id = i + 1;
		i++;
	}
	if (pthread_create(&(stats.check_all), NULL, check_phil, &stats))
	{
		printf("Error creating Thread\n");
		exit(1);
	}
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
	if (pthread_join(stats.check_all, NULL) != 0)
	{
		printf("Error creating Thread\n");
		exit(1);
	}
	return (NULL);
}

int main(int argc, char **av)
{
	t_philo	*philo;
	t_philo_stats stats;

	if (argc != 3)
		return (0);
	memset((void *)&stats, 0, sizeof(t_philo_stats));
	stats.nbr_phils = ft_atoi(av[1]);
	stats.time_to_die = ft_atoi(av[2]);
	philo = malloc(sizeof(t_philo) * stats.nbr_phils);
	stats.all = philo;
	philo->philo_id = 1;
	philos_init(stats, stats.nbr_phils);
	return (0);
}
