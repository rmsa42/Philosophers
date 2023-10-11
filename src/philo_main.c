/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:52:01 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/11 16:36:22 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int argc, char **av)
{
	t_philo			*philo;
	t_global_var	stats;

	if (argc == 5 || argc == 6)
	{
		philo = NULL;
		if (stats_init(&stats, av))
			return (0);
		if (philo_init(&philo, &stats))
			return (0);
		if (thread_init(&stats))
		{
			destroy_mutex(&stats, 3);
			return (0);
		}
	}
	return (0);
}
