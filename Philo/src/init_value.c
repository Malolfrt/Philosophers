/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 17:59:31 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/27 20:20:29 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->fork)
		return (0);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->fork[i], NULL ) != 0)
			return (0);
		i++;
	}
	if (pthread_mutex_init(&data->dead, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (0);
	return (1);
}

void	destroy_mutex(t_data *data)
{
	pthread_mutex_destroy(&data->write);
	pthread_mutex_destroy(&data->dead);
}

int	init_thread(t_data *data)
{
	int	i;

	i = 0;
	data->philo = malloc(sizeof(t_philo) * (data->nb_philo));
	if (!data->philo)
		return (0);
	while (i < data->nb_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].r_fork = i;
		data->philo[i].l_fork = (i + 1) % data->nb_philo;
		data->philo[i].meal_counter = 0;
		data->philo[i].full = false;
		data->philo[i].data = data;
		i++;
	}
	return (1);
}

void	init_value(t_data *data)
{
	if (!init_mutex(data))
	{
		destroy_mutex(data);
		free(data->fork);
		ft_error("Error : mutex_init");
	}
	if (!init_thread(data))
	{
		destroy_mutex(data);
		free(data->fork);
		free(data->philo);
		ft_error("Error : thread init");
	}
	data->is_dead = false;
	data->stop = false;
	gettimeofday(&data->start_time, NULL);
}
