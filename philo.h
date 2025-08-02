/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:58:25 by jmanson           #+#    #+#             */
/*   Updated: 2024/10/29 16:42:25 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include "philo.h"

struct	s_arg;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
	time_t			time_last_meal;
	int				life_limit;
	int				status;
	int				eating;
	pthread_mutex_t	*l_f;
	pthread_mutex_t	*r_f;
	struct s_arg	*arg;
}					t_philo;

typedef struct s_arg
{
	int				philo_n;
	int				threads_n;
	time_t			start_time;
	int				life_limit;
	int				eat_time;
	int				sleep_time;
	int				meals_target;
	int				stop;
	int				full;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	lock_full;
	pthread_mutex_t	lock_stop;
	pthread_mutex_t	lock_meals;
	t_philo			*philos;
}	t_arg;

void	taking_forks(t_philo *philo);
void	eating(t_philo *philo);
void	sleep_think(t_philo *philo);
long	ft_time(void);
void	ft_usleep(int ms);
int		ft_atoi(const char *str);
int		ft_is_digit(char *str);
int		meal_counter(t_philo *philo);
int		ft_monitor(t_philo *philo);
void	*process(void *args);
void	case_one(t_philo *p);
void	init_philos(t_arg *args);
void	init_mutex(t_arg *args);
int		init_threads(t_arg *args);
void	end_threads(t_arg *args);
int		init_args(t_arg *args, int argc, char **argv);
int		invalid_args(void);
int		check_valid(int argc, char **argv);
void	free_all(t_arg *args);
void	destroy_mutex(t_arg *args);
void	*ft_stop(void *args);
int		abs(int n);
int		stop(t_philo *philo);
void	monitor(t_philo *philo);
int		x_read(pthread_mutex_t *mutex, int *val);

#endif
