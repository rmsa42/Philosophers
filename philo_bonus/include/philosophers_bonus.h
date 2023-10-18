/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:43:14 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/18 16:34:13 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_philo
{
	int						philo_id;
	int						meals_nbr;
	int						philo_full;
	long long				last_eat;
	struct s_global_var		*data;
}				t_philo;

typedef struct s_global_var
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
	long long		time_ms;
	int				nbr_phils;
	int				end;
	pthread_t		monitor;
	pid_t			*p;
	sem_t			*sem1;
	sem_t			*last_eat_sem;
}			t_global_var;

//Utils
long long	start_time(void);
int	ft_atoi(const char *str);
void	put_msg(int philo_id, long long time, char c);

//philo routine
void	process_routine(t_philo *philo);

#endif