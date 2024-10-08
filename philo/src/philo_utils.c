/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:43:18 by rumachad          #+#    #+#             */
/*   Updated: 2024/08/13 16:25:30 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	start_time(void)
{
	struct timeval	time;
	long long		time_ml;

	gettimeofday(&time, NULL);
	time_ml = (time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ml);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	c;
	int			a;

	a = 1;
	c = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			a = a * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		c = (str[i] - '0') + (c * 10);
		i++;
	}
	if ((c * a) > 2147483647 || (c * a) <= 0 || str[i] != '\0')
		return (-1);
	else
		return (c * a);
}

void	put_msg(t_philo *philo, char c)
{
	long long	tmp;

	pthread_mutex_lock(&philo->data->print);
	tmp = start_time() - philo->data->time_ms;
	if (c == 'L' || c == 'R')
		printf("%lld %d has taken a fork\n", tmp, philo->philo_id);
	else if (c == 'E')
		printf("%lld %d is eating\n", tmp, philo->philo_id);
	else if (c == 'S')
		printf("%lld %d is sleeping\n", tmp, philo->philo_id);
	else if (c == 'T')
		printf("%lld %d is thinking\n", tmp, philo->philo_id);
	else if (c == 'D')
		printf("%lld %d died\n", tmp, philo->philo_id);
	pthread_mutex_unlock(&philo->data->print);
}

void	clean_program(t_global_var *data, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_destroy(&data->last_eat_lock);
		printf("Error initiating mutex meals\n");
	}
	else if (flag == 2)
	{
		pthread_mutex_destroy(&data->last_eat_lock);
		pthread_mutex_destroy(&data->meals_nbr_lock);
		printf("Error initiating mutex philo_dead\n");
	}
	else if (flag == 3)
	{
		pthread_mutex_destroy(&data->last_eat_lock);
		pthread_mutex_destroy(&data->meals_nbr_lock);
		pthread_mutex_destroy(&data->philo_dead);
	}
	if (data->forks)
	{
		pthread_mutex_destroy(data->forks);
		free(data->forks);
	}
	if (data->all)
		free(data->all);
}
