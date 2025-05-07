/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinning.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 19:22:02 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/28 14:47:09 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo (*philo) = (t_philo *)arg;
	philo->last_meal = get_time(philo->data);
	if (philo->data->nb_philo == 1)
	{
		print_one(philo);
		return (NULL);
	}
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			if (!odd_id(philo))
				break ;
		}
		else
			if (!even_id(philo))
				break ;
		philo->meal_counter++;
		if (philo->meal_counter == philo->data->max_meal)
			break ;
		if (!eating_and_thinking(philo))
			break ;
	}
	return (NULL);
}

int	need_exit(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead);
	if (philo->data->is_dead == true)
	{
		pthread_mutex_unlock(&philo->data->dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead);
	if (monitoring(philo))
		return (1);
	return (0);
}

int	odd_id(t_philo *philo)
{
	if (need_exit(philo))
		return (0);
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	if (need_exit(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		return (0);
	}
	print_all(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	if (need_exit(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		return (0);
	}
	print_all(philo, "is eating\n");
	usleep(philo->data->time_to_eat);
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	return (1);
}

int	even_id(t_philo *philo)
{
	if (need_exit(philo))
		return (0);
	pthread_mutex_lock(&philo->data->fork[philo->l_fork]);
	if (need_exit(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		return (0);
	}
	print_all(philo, "has taken a fork\n");
	pthread_mutex_lock(&philo->data->fork[philo->r_fork]);
	if (need_exit(philo))
	{
		pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
		pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
		return (0);
	}
	print_all(philo, "is eating\n");
	usleep(philo->data->time_to_eat);
	philo->last_meal = get_time(philo->data);
	pthread_mutex_unlock(&philo->data->fork[philo->l_fork]);
	pthread_mutex_unlock(&philo->data->fork[philo->r_fork]);
	return (1);
}

void	dinning(t_data *data)
{
	pthread_t	*thread;
	int			i;

	i = 0;
	thread = malloc(sizeof(pthread_t) * (data->nb_philo));
	if (!thread)
		return ;
	while (i < data->nb_philo)
	{
		if (pthread_create(&thread[i], NULL, &routine,
				(void *)&data->philo[i]) != 0)
			return (free(thread));
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	free(thread);
}
