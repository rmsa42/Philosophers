/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/10 16:42:30 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	main(int argc, char **av)
{
	t_philo			*philo;
	t_philo_stats	stats;

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
		thread_init(&stats);
	}
	return (0);
}
