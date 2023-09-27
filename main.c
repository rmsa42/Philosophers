/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:03:03 by rumachad          #+#    #+#             */
/*   Updated: 2023/09/27 16:53:54 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str);

void *mk_thread(void *arg)
{
	int *nbr;

	nbr = (int *)arg;
	printf("Thread Created: %d\n", *nbr);
	return (NULL);
}

void *thread_init(pthread_t **test, int phil_nbr)
{
	int i;
	int err;

	i = 0;
	err = 0;
	*test = (pthread_t *)malloc(sizeof(pthread_t) * (phil_nbr));
	if (*test == NULL)
		return (NULL);
    while (i < phil_nbr)
	{
		err = pthread_create(&(*test[i]), NULL, mk_thread, &i);
		if (err)
		{
			printf("Error");
			return (0);
		}
		pthread_join((*test[i]), NULL);
		i++;
	}
	return (NULL);
}

int main(int argc, char **av)
{
    pthread_t *test;
	int phil_nbr;

	if (argc != 2)
		return (0);
	phil_nbr = ft_atoi(av[1]);
	thread_init(&test, phil_nbr);
	return (0);
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
