/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmanson <jmanson@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:55:04 by jmanson           #+#    #+#             */
/*   Updated: 2024/10/21 17:32:34 by jmanson          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*This function gets the current time in ms. It calls 
gettimeofday and stores the data in a timeval struct. 
Then it converts the time to milliseconds.*/
long	ft_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (1000 * (size_t)tv.tv_sec + (size_t)tv.tv_usec / 1000);
}

/*This function is an adaptation of usleep. It 
first stores the current time in ms. Then usleep 
is called for ms * 920 microseconds. Then a loop is 
used to check if the current time is less than the 
beginning time + the input time ms. While it is less 
usleep is repeatedly called for ms * 3 microseconds.*/
void	ft_usleep(int ms)
{
	long int	start;

	start = ft_time();
	usleep(ms * 920);
	while (ft_time() <= start + ms)
		usleep(ms);
}

static int	ft_isspace(int c)
{
	if (c == ' ' || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	i;

	res = 0;
	i = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			i = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - 48);
		++str;
	}
	return (res * i);
}

int	ft_is_digit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}
