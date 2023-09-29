/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:41:36 by rumachad          #+#    #+#             */
/*   Updated: 2023/09/29 17:20:30 by rumachad         ###   ########.fr       */
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
	int			time_alive;
	struct s_philo_stats	*data;
}				t_philo;

typedef struct s_philo_stats
{
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			nbr_phils;
	t_philo		*all;  		//pointer to all threads(philosophers)
	pthread_mutex_t *forks;
}			t_philo_stats;

//Utils
int	start_time(void);
int	ft_atoi(const char *str);

//Check_all Function
/* void    *check_phil(t_philo_stats *stats); */

#endif