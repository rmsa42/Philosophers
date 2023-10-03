/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:36:44 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/03 16:50:14 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

void	check_phil(t_philo *philo)
{
	long long	tmp;

	tmp = start_time() - philo->last_eat;
	printf("%lld\n", tmp);
	if (tmp >= philo->data->time_to_die)
	{
		printf("Phil %d died\n", philo->philo_id);
	}
	return ;
}