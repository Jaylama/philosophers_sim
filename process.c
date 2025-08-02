/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:07:27 by jmanson           #+#    #+#             */
/*   Updated: 2024/10/29 16:44:58 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_process(t_arg *arg)
{
	pthread_mutex_lock(&arg->lock_stop);
	arg->stop = 1;
	pthread_mutex_unlock(&arg->lock_stop);
}

/*This function checks if the philo has eaten the 
target number of meals or more. If so status is set 
to 1. The full variable is incremented by one to 
count the number of full philos. If full is greater 
than or equal to the number of philos arg->stop is set 
to 1. It returns 1 if the philo is full so that the 
thread can be ended.*/
int	meal_counter(t_philo *p)
{
	int	target;

	target = p->arg->meals_target;
	if (target > 0 && (x_read(&p->arg->lock_meals, &p->meals_eaten) >= target))
	{
		pthread_mutex_lock(&p->arg->lock_full);
		p->status = 1;
		p->arg->full++;
		if (p->arg->full >= p->arg->philo_n)
			end_process(p->arg);
		pthread_mutex_unlock(&p->arg->lock_full);
		return (1);
	}
	return (0);
}

/*This function checks if the process should continue. 
First it returns if stop is already >0. 
Then it calls the meal counter function to check if 
the philo has eaten enough. Then it sets the time 
variable as the time elapsed since the last meal. 
If time is greater than the life_limit variable, the 
philo dies, and time of death is set. It returns zero 
if none of these cases are true.*/
int	stop(t_philo *p)
{
	long	time;
	long	t_ofdeath;

	if (x_read(&p->arg->lock_stop, &p->arg->stop))
		return (1);
	if (meal_counter(p))
		return (0);
	pthread_mutex_lock(&p->arg->lock_meals);
	time = ft_time() - p->time_last_meal;
	pthread_mutex_unlock(&p->arg->lock_meals);
	if (time > p->life_limit && !p->eating)
	{
		t_ofdeath = ft_time() - p->arg->start_time;
		end_process(p->arg);
		usleep(6000);
		printf("%ld %d died\n", t_ofdeath, p->id);
		return (1);
	}
	return (0);
}

/*This function is the process each philo will 
loop through until they either die or have eaten 
enough. The philo will pick up forks, eat, sleep 
and then think. The function stop is called 
periodically to check if the philo has eaten 
enough or has died. If there is only one philo it
will pick up a single fork until it dies.*/
void	*process(void *philo)
{
	t_philo		*p;

	p = (t_philo *)philo;
	pthread_mutex_lock(&p->arg->lock_meals);
	p->time_last_meal = ft_time();
	pthread_mutex_unlock(&p->arg->lock_meals);
	while (!stop(p))
	{
		if (p->arg->philo_n == 1)
			printf("%ld %d has taken a fork\n", \
			ft_time() - p->arg->start_time, p->id);
		else
		{
			taking_forks(philo);
			eating(philo);
			sleep_think(philo);
		}
	}
	return (NULL);
}
