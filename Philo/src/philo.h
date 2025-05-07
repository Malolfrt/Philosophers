/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlefort <mlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:04:22 by mlefort           #+#    #+#             */
/*   Updated: 2024/03/28 16:57:43 by mlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h> // malloc,free...
# include <stdio.h> // printf...
# include <strings.h> // memset...
# include <unistd.h> // write, usleep...
# include <pthread.h> // pthread_...
# include <sys/time.h> // gettimeofday...
# include <limits.h> // INT_MAX...
# include <stdbool.h> // bool...

typedef struct s_data	t_data;

typedef struct s_philo
{
	int				id;
	long			last_meal;
	int				l_fork;
	int				r_fork;
	long			meal_counter;
	bool			full;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;
	t_data			*data;
}	t_philo;

typedef struct s_data
{
	long			nb_philo;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_to_died;
	long			max_meal;
	bool			is_dead;
	bool			stop;
	pthread_mutex_t	*fork;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	struct timeval	start_time;
	t_philo			*philo;
}	t_data;

/*		utils.c		*/
void	ft_error(char *str);
long	ft_atol(char *str);
void	cleanup(t_data *data);
long	get_time(t_data *data);
void	check_dead_time(t_philo *philo);

/*		parsing.c		*/
void	parsing(t_data *data, char **av);

/*		init_value.c		*/
void	init_value(t_data *data);
int		init_thread(t_data *data);

/*		dinning.c		*/
void	*routine(void *arg);
int		need_exit(t_philo *philo);
int		odd_id(t_philo *philo);
int		even_id(t_philo *philo);
void	dinning(t_data *data);

/*		dinning_utils.c		*/
void	print_time(t_data *data);
void	print_all(t_philo *philo, char *str);
int		monitoring(t_philo *philo);
void	print_one(t_philo *philo);
int		eating_and_thinking(t_philo *philo);

#endif