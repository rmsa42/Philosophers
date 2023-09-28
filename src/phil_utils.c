/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phil_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 14:49:46 by rumachad          #+#    #+#             */
/*   Updated: 2023/09/28 16:35:48 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philosophers.h"

int	start_time(void)
{
	struct timeval time;
	int				time_ml;
	
	if (gettimeofday(&time, NULL) != 0)
	{
		printf("Error");
		exit(1);
	}
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
	if ((c * a) > 2147483647 || (c * a) < -2147483648)
		return (0);
	else
		return (c * a);
}
