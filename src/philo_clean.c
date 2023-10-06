/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_clean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:40:32 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/06 17:09:57 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	destroy_mutex(t_philo_stats *stats)
{
	int	i;

	i = 0;
	free(stats->all);
	while (i < stats->nbr_phils)
	{
		pthread_mutex_destroy(&stats->forks[i]);
		i++;
	}
	free(stats->forks);
}
