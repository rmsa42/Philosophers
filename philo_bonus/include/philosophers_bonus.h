/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rumachad <rumachad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:43:14 by rumachad          #+#    #+#             */
/*   Updated: 2023/10/17 16:45:44 by rumachad         ###   ########.fr       */
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
}			t_global_var;

//Utils
long long	start_time(void);
int	ft_atoi(const char *str);
void	put_msg(int philo_id, long long time, char c);

#endif