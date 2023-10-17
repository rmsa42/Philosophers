/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 16:23:03 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/17 16:45:25 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

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
		return (0);
	else
		return (c * a);
}

void	put_msg(int philo_id, long long time, char c)
{
	long long	tmp;

	tmp = start_time() - time;
	if (c == 'L' || c == 'R')
		printf("%lld %d has taken a fork\n", tmp, philo_id);
	else if (c == 'E')
		printf("%lld %d is eating\n", tmp, philo_id);
	else if (c == 'S')
		printf("%lld %d is sleeping\n", tmp, philo_id);
	else if (c == 'T')
		printf("%lld %d is thinking\n", tmp, philo_id);
	else if (c == 'D')
		printf("%lld %d died\n", tmp, philo_id);
}
