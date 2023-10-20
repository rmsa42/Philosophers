/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:43:14 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/20 15:12:04 by rumachad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <stdio.h>
# include <signal.h>
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
	pid_t			*pid;
	sem_t			*forks_sem;
	sem_t			*last_eat_sem;
	sem_t			*death_sem;
	sem_t			*meals_sem;
	sem_t			*print_sem;
}			t_global_var;

//Utils
long long	start_time(void);
int			ft_atoi(const char *str);
void		put_msg(t_philo *philo, char c);
void		clean_program(t_global_var *data);

//philo routine
void		process_routine(t_philo *philo);

//Checks
int			check_alive(t_global_var *data);
void		kill_dead(t_philo *philo);
void		*monitoring(void *arg);

//Init
void		init_sem(t_global_var *data);
int			data_init(t_global_var *data, char **av);

#endif