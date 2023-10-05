/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rui <rui@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:41:36 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/05 18:03:06 by rui              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t	thread_philo;
	int			philo_id;
	int			meals_nbr;
	long long	last_eat;   //Last time it ate(in ms)
	int			philo_meals;
	struct s_philo_stats	*data;
}				t_philo;

typedef struct s_philo_stats
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_meals;
	long long	time_ms;     //Time threads start(in ms)
	int			nbr_phils;
	t_philo		*all;  		//pointer to all threads(philosophers)
	pthread_mutex_t *forks;
}			t_philo_stats;

//Utils
long long	start_time(void);
int	ft_atoi(const char *str);

//Check_all Function
int	check_phil(t_philo *philo);

#endif