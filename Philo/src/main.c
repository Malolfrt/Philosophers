/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 13:51:01 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/28 14:23:06 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		ft_error("not enough arguments or too many arguments");
	parsing(&data, av);
	init_value(&data);
	dinning(&data);
	cleanup(&data);
	return (0);
}
