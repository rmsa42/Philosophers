/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:30 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/18 16:42:42 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_processes(t_global_var *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nbr_phils)
	{
		printf("asds\n");
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < data->nbr_phils)
			{
				kill(data->p[i], SIGKILL);
				i++;
			}
		}
		i++;
	}
	sem_close(data->sem1);
	sem_close(data->last_eat_sem);
}

int	data_init(t_global_var *data, char **av)
{
	data->nbr_phils = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->p = (pid_t *)malloc(sizeof(pid_t) * data->nbr_phils);
	if (data->p == NULL)
	return (-1);
	data->end = 0;
	if (av[5])
		data->nbr_meals = ft_atoi(av[5]);
	else
		data->nbr_meals = -1;
	if (data->nbr_phils == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| data->nbr_meals == 0)
	{
		printf("Invalid Arguments\n");
		return (-1);
	}
	return (0);
}



void	init_processes(t_philo *philo, t_global_var *data)
{
	int		i;

	i = 0;
	data->time_ms = start_time();
	while (i < data->nbr_phils)
	{
		philo->philo_id = i + 1;
		philo->last_eat = start_time();
		data->p[i] = fork();
		if (data->p[i] < 0)
		{
			printf("Error Creating Processes\n");
			exit(EXIT_FAILURE);
		}
		if (data->p[i] == 0)
		{
			process_routine(philo);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

int main(int argc, char *av[])
{
	t_philo	philo;
	t_global_var data;
	
	if (argc == 5 || argc == 6)
	{
		memset((void *)&data, 0, sizeof(t_global_var));
		memset((void *)&philo, 0, sizeof(t_philo));
		philo.data = &data;
		if (data_init(&data, av) == -1)
			exit(EXIT_FAILURE);
		sem_unlink("fork");
		sem_unlink("last_eat");
		data.sem1 = sem_open("fork", O_CREAT | O_EXCL, 0600, data.nbr_phils);
		data.last_eat_sem = sem_open("last_eat", O_CREAT | O_EXCL, 0600, 1);
		if (data.sem1 == SEM_FAILED)
			exit(EXIT_FAILURE);
		init_processes(&philo, &data);
		close_processes(&data);
	}
	return (0);
}
