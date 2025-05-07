/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:34:58 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/27 19:42:12 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	parsing(t_data *data, char **av)
{
	data->nb_philo = ft_atol(av[1]);
	data->time_to_died = ft_atol(av[2]) * 1e3;
	data->time_to_eat = ft_atol(av[3]) * 1e3;
	data->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (av[5])
		data->max_meal = ft_atol(av[5]);
	else
		data->max_meal = -1;
	if ((data->time_to_died < 6e4)
		|| (data->time_to_eat < 6e4)
		|| (data->time_to_sleep < 6e4))
		ft_error("Too less time to process");
	if (data->nb_philo == 0)
		ft_error("Need to have philosophers");
	if (data->nb_philo > 200)
		ft_error("Too many philosophers");
}
