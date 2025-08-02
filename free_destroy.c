/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:07:45 by jmanson           #+#    #+#             */
/*   Updated: 2024/06/06 14:30:20 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_arg *args)
{
	free(args->tids);
	free(args->philos);
	free(args->forks);
	return ;
}

void	destroy_mutex(t_arg *args)
{
	int	np;

	np = args->philo_n;
	while (np--)
		pthread_mutex_destroy(&args->forks[np]);
	pthread_mutex_destroy(&args->lock_full);
	pthread_mutex_destroy(&args->lock_stop);
	pthread_mutex_destroy(&args->lock_meals);
}

/*This function loops through the threads, calling pthread 
join for each. If pthread_join fails, i is set to the philo 
number and it is called again at the end.*/
void	end_threads(t_arg *args)
{
	int	np;
	int	i;

	i = 0;
	np = 0;
	while (np < args->philo_n)
	{
		if (pthread_join(args->tids[np], NULL))
			i = np + 1;
		np++;
	}
	if (i)
		pthread_join(args->tids[i - 1], NULL);
}

int	invalid_args(void)
{
	printf("		Invalid argument(s)...		      \n");
	printf("           Please enter 4 or 5 numerical arguments:   \n");
	printf(" ____________________________________________________ \n");
	printf("|             [1][Number of philosophers]            |\n");
	printf("|             [2][Time w/o food until dies]          |\n");
	printf("|             [3][Eating time]                       |\n");
	printf("|             [4][Sleeping time]                     |\n");
	printf("|             [5][Number of meals]                   |\n");
	printf("|____________________________________________________|\n");
	return (1);
}
