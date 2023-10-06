/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:42:55 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/06 17:08:54 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_phil(t_philo_stats *data)
{
	long long	tmp;
	int			i;
	int			count;

	count = 0;
	while (!data->end)
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
		if (count == data->nbr_phils)
			break ;
	}
	return ;
}
 