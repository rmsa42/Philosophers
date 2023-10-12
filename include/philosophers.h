/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 12:41:36 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/12 14:16:35 by rumachad         ###   ########.fr       */
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
	pthread_t				thread_philo;
	int						philo_id;
	int						meals_nbr;
	long long				last_eat;
	int						philo_meals;
	struct s_global_var		*data;
}				t_philo;

typedef struct s_global_var
{
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				nbr_meals;
	int				end;
	long long		time_ms;
	int				nbr_phils;
	int				all_ate;
	t_philo			*all;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_eat_lock;
	pthread_mutex_t	meals_nbr_lock;
	pthread_mutex_t	philo_dead;
}			t_global_var;

//Utils
long long	start_time(void);
int			ft_atoi(const char *str);
void		put_msg(t_philo *philo, char c);
//Destroy Mutex/Free functions
void		destroy_mutex(t_global_var *stats, int flag);

//Check_all Function
void		philo_monitor(t_global_var *data);
int			check_alive(t_global_var *data);

//pthread_create call function
void		*thread_start(void *arg);

//Init Threads and Structs
int			thread_init(t_global_var *stats);
int			philo_init(t_philo **philo, t_global_var *stats);
int			stats_init(t_global_var *stats, char **av);

#endif