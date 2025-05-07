/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:27:27 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/28 16:37:53 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	exit(1);
}

long	ft_atol(char *str)
{
	int		i;
	long	res;
	long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ft_error("We need only positive input");
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
		if (i > 10)
			return (0);
	}
	return (res * neg);
}

long	get_time(t_data *data)
{
	struct timeval	current_time;
	long			res;

	gettimeofday(&current_time, NULL);
	res = (current_time.tv_sec - data->start_time.tv_sec)
		* 1000 + (current_time.tv_usec - data->start_time.tv_usec) / 1000;
	return (res);
}

void	check_dead_time(t_philo *philo)
{
	if (philo->data->time_to_died > philo->data->time_to_sleep
		&& philo->data->time_to_died > philo->data->time_to_eat
		&& philo->data->time_to_died < philo->data->time_to_eat
		+ philo->data->time_to_sleep)
	{
		philo->data->time_to_sleep = philo->data->time_to_died;
		philo->data->time_to_eat = philo->data->time_to_died;
	}
	else if (philo->data->time_to_died <= philo->data->time_to_sleep
		|| philo->data->time_to_died <= philo->data->time_to_eat)
	{
		philo->data->time_to_sleep = philo->data->time_to_died;
		philo->data->time_to_eat = philo->data->time_to_died;
	}
}

void	cleanup(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead);
	free(data->philo);
	free(data->fork);
}
