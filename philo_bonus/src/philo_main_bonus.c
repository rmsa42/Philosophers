/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_main_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:28:55 by rumachad          #+#    #+#             */
/*   Updated: 2023/11/02 11:12:57 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	meals_check(t_philo *philo)
{
	sem_wait(philo->data->meals_sem);
	if (philo->meals_nbr == philo->data->nbr_meals)
	{
		sem_post(philo->data->meals_sem);
		return (1);
	}
	sem_post(philo->data->meals_sem);
	return (0);
}

void	*monitoring(void *arg)
{
	int		tmp;
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		sem_wait(philo->data->last_eat_sem);
		tmp = start_time() - philo->last_eat;
		sem_post(philo->data->last_eat_sem);
		if (tmp >= philo->data->time_to_die)
		{
			put_msg(philo, 'D');
			exit(EXIT_FAILURE);
		}
		if (philo->data->nbr_meals != -2)
		{
			if (meals_check(philo))
				break ;
		}
	}
	return (NULL);
}

void	close_processes(t_global_var *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nbr_phils)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < data->nbr_phils)
			{
				kill(data->pid[i], SIGKILL);
				i++;
			}
		}
		i++;
	}
	clean_program(data);
}

void	init_processes(t_philo *philo, t_global_var *data)
{
	int		i;

	i = 0;
	data->time_ms = start_time();
	while (i < data->nbr_phils)
	{
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			printf("Error Creating Processes\n");
			exit(EXIT_FAILURE);
		}
		if (data->pid[i] == 0)
		{
			philo->philo_id = i + 1;
			philo->last_eat = start_time();
			process_routine(philo);
		}
		i++;
	}
}

int	main(int argc, char *av[])
{
	t_philo			philo;
	t_global_var	data;

	if (argc == 5 || argc == 6)
	{
		memset((void *)&data, 0, sizeof(t_global_var));
		memset((void *)&philo, 0, sizeof(t_philo));
		philo.data = &data;
		if (data_init(&data, av) == -1)
			exit(EXIT_FAILURE);
		init_sem(&data);
		init_processes(&philo, &data);
		close_processes(&data);
	}
	else
		printf("Invalid number of arguments\n");
	return (0);
}
