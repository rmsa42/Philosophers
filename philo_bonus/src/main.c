/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:30 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/20 15:13:32 by rumachad         ###   ########.fr       */
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
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			sem_post(data->death_sem);
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
		philo->philo_id = i + 1;
		philo->last_eat = start_time();
		data->pid[i] = fork();
		if (data->pid[i] < 0)
		{
			printf("Error Creating Processes\n");
			exit(EXIT_FAILURE);
		}
		if (data->pid[i] == 0)
			process_routine(philo);
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
		init_sem(&data);
		init_processes(&philo, &data);
		close_processes(&data);
	}
	return (0);
}
