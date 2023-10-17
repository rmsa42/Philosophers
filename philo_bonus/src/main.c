/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:42:30 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/17 16:53:07 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

void	close_processes(t_global_var *data, sem_t *se)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->nbr_phils)
	{
		waitpid(-1, &status, 0);
		i++;
	}
	sem_unlink("fork");
	sem_close(se);
}

int	data_init(t_global_var *data, char **av)
{
	data->nbr_phils = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
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

void	init_processes(t_philo *philo, t_global_var *data, sem_t *se)
{
	int		i;
	pid_t	p;

	i = 0;
	data->time_ms = start_time();
	while (i < data->nbr_phils)
	{
		philo->philo_id = i + 1;
		philo->last_eat = start_time();
		p = fork();
		if (p < 0)
		{
			printf("Error Creating Processes\n");
			exit(EXIT_FAILURE);
		}
		if (p == 0)
		{
			sem_wait(se);
			put_msg(philo->philo_id, data->time_ms, 'L');
			sleep(1);
			sem_post(se);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
}

int main(int argc, char *av[])
{
	t_philo	philo;
	t_global_var data;
	sem_t *se;
	
	if (argc == 5 || argc == 6)
	{
		se = sem_open("fork", O_CREAT | O_EXCL, 00700, 1);
		if (se == SEM_FAILED)
			exit(EXIT_FAILURE);
		memset((void *)&philo, 0, sizeof(t_philo));
		memset((void *)&data, 0, sizeof(t_global_var));
		data_init(&data, av);
		init_processes(&philo, &data, se);
		close_processes(&data, se);
	}
	return (0);
}
