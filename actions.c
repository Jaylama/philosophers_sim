/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:08:28 by jmanson           #+#    #+#             */
/*   Updated: 2024/10/29 17:01:42 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	x_read(pthread_mutex_t *mutex, int *val)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *val;
	pthread_mutex_unlock(mutex);
	return (ret);
}

/*First the fork mutexes are locked. THen it checks if the proess should 
continue and prints a message that the philo has taken forks.*/
void	taking_forks(t_philo *p)
{
	pthread_mutex_lock(p->l_f);
	pthread_mutex_lock(p->r_f);
	if (x_read(&p->arg->lock_stop, &p->arg->stop) || meal_counter(p))
		return ;
	printf("%ld %d has taken a fork\n", ft_time() - p->arg->start_time, p->id);
	printf("%ld %d has taken a fork\n", ft_time() - p->arg->start_time, p->id);
}

/*First it checks if the process should continue. If so, it sets the eating 
flag to 1 then prints a message that the philo is eating. Then the meals mutex 
is locked, meals_eaten is incremented, time_last_meal is set to the current 
time, and the meals mutex is unlocked. Then ft_usleep is called for the 
eating time, andthe eating flag is set to 0 again. Finally the mutexes are 
unlocked.*/
void	eating(t_philo *p)
{
	if (!x_read(&p->arg->lock_stop, &p->arg->stop))
	{
		p->eating = 1;
		pthread_mutex_lock(&p->arg->lock_meals);
		p->meals_eaten += 1;
		p->time_last_meal = ft_time();
		pthread_mutex_unlock(&p->arg->lock_meals);
		printf("%ld %d is eating\n", ft_time() - p->arg->start_time, p->id);
		ft_usleep(p->arg->eat_time - 1);
		p->eating = 0;
	}
	pthread_mutex_unlock(p->l_f);
	pthread_mutex_unlock(p->r_f);
}

void	sleep_think(t_philo *p)
{
	if (!x_read(&p->arg->lock_stop, &p->arg->stop) && !meal_counter(p))
		printf("%ld %d is sleeping\n", ft_time() - p->arg->start_time, p->id);
	ft_usleep(p->arg->sleep_time - 1);
	if (!x_read(&p->arg->lock_stop, &p->arg->stop) && !meal_counter(p))
		printf("%ld %d is thinking\n", ft_time() - p->arg->start_time, p->id);
}
