/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:07:54 by jmanson           #+#    #+#             */
/*   Updated: 2024/10/29 16:41:45 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	abs(int n)
{
	if (n < 0)
		return (n * -1);
	else
		return (n);
}

/*This function first allocates memory to each location 
in the philos array. Then the variables for each philo 
are initialised using a while loop. The left fork for 
each philo is set as the index of the philo. The right 
fork is set as the index - 1 for all philos except the 
first one, which is set to the total number of philos - 1 
(i.e. the highest index).*/
void	init_philos(t_arg *args)
{
	int		i;
	t_philo	*philos;

	i = 0;
	philos = malloc(sizeof(t_philo) * args->philo_n);
	if (!philos)
		philos = malloc(sizeof(t_philo) * args->philo_n);
	while (i < args->philo_n)
	{
		philos[i].id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].life_limit = args->life_limit;
		philos[i].time_last_meal = ft_time();
		philos[i].status = 0;
		philos[i].eating = 0;
		philos[i].l_f = &args->forks[i];
		if (args->philo_n > 1)
		{
			philos[i].r_f = &args->forks[abs(i - 1)];
			philos[0].r_f = &args->forks[args->philo_n - 1];
		}
		philos[i].arg = args;
		i++;
	}
	args->philos = philos;
}

/*First memory is allocated to the threads array. Then the start 
time is set to current time. Next pthread_create is called for 
each of the philos. Then the threads are assigned to the tids variable
and the monitor function is called. */
int	init_threads(t_arg *args)
{
	int			np;
	pthread_t	*t;
	t_philo		*phil;

	phil = args->philos;
	np = args->philo_n;
	t = malloc(sizeof(pthread_t) * np);
	if (!t)
		t = malloc(sizeof(pthread_t) * np);
	args->start_time = ft_time();
	while (np--)
		if (pthread_create(&t[np], NULL, process, (void *)&phil[np]))
			np++;
	args->tids = t;
	monitor(phil);
	return (0);
}

/*First memory is allocated to the mutex array. Then 
pthread_mutex_init is called for each location in the 
array. Finally mutexes are intialised to lock the full
and stop variables, and the meals counter.*/
void	init_mutex(t_arg *args)
{
	int				np;
	pthread_mutex_t	*mutex;

	np = args->philo_n;
	mutex = malloc(sizeof(pthread_mutex_t) * np);
	if (!mutex)
		mutex = malloc(sizeof(pthread_mutex_t) * np);
	while (np--)
		if (pthread_mutex_init(&mutex[np], NULL))
			np++;
	pthread_mutex_init(&args->lock_full, NULL);
	pthread_mutex_init(&args->lock_stop, NULL);
	pthread_mutex_init(&args->lock_meals, NULL);
	args->forks = mutex;
}

/*This function takes the argv inputs and assigns them to 
respective variables. Then it initialises the remaining 
values and sets the number of threads equal to the number 
of philosophers. If there is no meals target, it is set to 
-1, otherwise the input from the 5th arg is assigned.*/
int	init_args(t_arg *args, int argc, char **argv)
{
	args->philo_n = ft_atoi(argv[1]);
	args->life_limit = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	args->stop = 0;
	args->full = 0;
	args->threads_n = args->philo_n;
	if (args->philo_n < 1)
		return (0);
	args->meals_target = -1;
	if (argc == 6)
	{
		args->meals_target = ft_atoi(argv[5]);
		if (args->meals_target < 1)
			return (0);
	}
	return (0);
}
