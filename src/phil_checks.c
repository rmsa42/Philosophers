/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_checks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 16:36:44 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/05 18:05:39 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	check_phil(t_philo *philo)
{
	long long	tmp;

	if (philo->last_eat == 0)
		return (0);
	tmp = start_time() - philo->last_eat;
	if (tmp >= philo->data->time_to_die)
	{
		printf("Phil %d died\n", philo->philo_id);
		return (1);
	}
	if (philo->meals_nbr == philo->data->nbr_meals)
		return (1);
	return (0);
}