/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 12:46:49 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/20 15:11:43 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers_bonus.h"

int	data_init(t_global_var *data, char **av)
{
	data->nbr_phils = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->pid = (pid_t *)malloc(sizeof(pid_t) * data->nbr_phils);
	if (data->pid == NULL)
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

void	init_sem(t_global_var *data)
{
	sem_unlink("forks");
	sem_unlink("last_eat");
	sem_unlink("death");
	sem_unlink("meals");
	sem_unlink("print");
	data->forks_sem = sem_open("forks", O_CREAT | O_EXCL, 0600, data->nbr_phils);
	if (data->forks_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->last_eat_sem = sem_open("last_eat", O_CREAT | O_EXCL, 0600, 1);
	if (data->last_eat_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->death_sem = sem_open("death", O_CREAT | O_EXCL, 0600, 1);
	if (data->death_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->meals_sem = sem_open("meals", O_CREAT | O_EXCL, 0600, 1);
	if (data->meals_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
	data->print_sem = sem_open("print", O_CREAT | O_EXCL, 0600, 1);
	if (data->print_sem == SEM_FAILED)
		exit(EXIT_FAILURE);
}
