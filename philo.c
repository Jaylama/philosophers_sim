/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:07:16 by jmanson           #+#    #+#             */
/*   Updated: 2024/07/01 13:18:50 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_valid(int argc, char **argv)
{
	size_t	i;

	if (argc < 5 || argc > 6)
		return (invalid_args());
	i = 0;
	while (argv[++i])
	{
		if (!ft_is_digit(argv[i]) || (!ft_atoi(argv[i])))
			return (invalid_args());
	}
	return (0);
}

/*this loops through each philo and checks them with 
 * the stop function. If the stop variable is equal 
 * to 1, the threads will be ended, the mutexes 
 * destroyed and memory freed.*/
void	monitor(t_philo *philo)
{
	int	i;

	i = philo->arg->philo_n;
	while (!stop(&philo[--i]))
	{
		if (i == 0)
			i = philo->arg->philo_n;
	}
	end_threads(philo->arg);
	destroy_mutex(philo->arg);
	free_all(philo->arg);
	return ;
}

/*The main function first checks the input is valid, then 
initialises the args struct, then initialises the mutexes, 
then initialises the philos structs, then initialises the 
threads.*/
int	main(int argc, char **argv)
{
	t_arg	args;

	if (check_valid(argc, argv))
		return (1);
	if (init_args(&args, argc, argv) == 1)
		return (1);
	init_mutex(&args);
	init_philos(&args);
	init_threads(&args);
	return (0);
}
