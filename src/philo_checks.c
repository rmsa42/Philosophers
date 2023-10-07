/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:55 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/07 16:11:49 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_phil(t_philo_stats *data)
{
	long long	tmp;
	int			i;
	int			count;

	count = 0;
	while (!data->end && count != data->nbr_phils)
	{
		i = 0;
		while (i < data->nbr_phils && !data->end)
		{
			tmp = start_time() - data->all[i].last_eat;
			if (tmp >= data->time_to_die)
			{
				printf("Philo %d died %lld\n", data->all[i].philo_id, tmp);
				data->end = 1;
			}
			if (data->all[i].meals_nbr == data->nbr_meals)
				count++;
			i++;
		}
	}
	return ;
}
 