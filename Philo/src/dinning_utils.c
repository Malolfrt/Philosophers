/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:34:15 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/28 16:37:56 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_all(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->write);
	print_time(philo->data);
	printf("%d %s", philo->id, str);
	pthread_mutex_unlock(&philo->data->write);
}

void	print_time(t_data *data)
{
	struct timeval	current_time;
	long			res;

	gettimeofday(&current_time, NULL);
	res = (current_time.tv_sec - data->start_time.tv_sec)
		* 1000 + (current_time.tv_usec - data->start_time.tv_usec) / 1000;
	printf("%ld ", res);
}

void	print_one(t_philo *philo)
{
	print_all(philo, "has taken a fork\n");
	usleep(philo->data->time_to_died);
	print_all(philo, "died\n");
}

int	eating_and_thinking(t_philo *philo)
{
	if (need_exit(philo))
		return (0);
	print_all(philo, "is sleeping\n");
	usleep(philo->data->time_to_sleep);
	if (need_exit(philo))
		return (0);
	print_all(philo, "is thinking\n");
	return (1);
}

int	monitoring(t_philo *philo)
{
	long	last_time;
	long	eat_sleep;
	long	current_time;

	current_time = get_time(philo->data);
	last_time = current_time - philo->last_meal;
	eat_sleep = philo->last_meal + (philo->data->time_to_sleep / 1000);
	if (last_time >= (philo->data->time_to_died / 1000))
	{
		pthread_mutex_lock(&philo->data->dead);
		philo->data->is_dead = true;
		print_all(philo, "died\n");
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	check_dead_time(philo);
	return (0);
}
