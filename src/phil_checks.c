/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:36:44 by rumachad          #+#    #+#             */
/*   Updated: 2023/09/29 11:59:29 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	*check_phil(t_philo_stats *stats)
{
	int	i;
	
	i = 0;
	while (1)
	{
		if (i == stats->nbr_phils)
			i = 0;
		if ((start_time() - stats->all[i].time_alive) >= stats->time_to_die)
		{
			printf("Phil %d Dead\n", stats->all[i].philo_id);
			break ;
		}
		i++;
	}
	return (NULL);
}