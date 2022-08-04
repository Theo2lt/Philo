/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 06:29:33 by tliot             #+#    #+#             */
/*   Updated: 2022/08/04 02:25:49 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// Init Argument ///
int	init_arg(t_data *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->running = true;
	data->count_done = 0;
	if (data->nbr_philo <= 0
		|| data->time_to_die <= 0
		|| data->time_to_sleep <= 0
		|| data->time_to_eat <= 0)
		return (1);
	if (argv[5])
	{
		data->nbr_eat = ft_atoi(argv[5]);
		if (data->nbr_eat <= 0)
			return (1);
	}
	else
		data->nbr_eat = -1;
	return (0);
}

/// Initialisation Philo ///
int	init_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i != data->nbr_philo)
	{
		data->philo[i].id = i;
		data->philo[i].left_fourch_id = i;
		data->philo[i].right_fourch_id = (i + 1) % data->nbr_philo;
		data->philo[i].data = data;
		data->philo[i].last_time_miam_miam = 0;
		data->philo[i].count_miam_miam = 0;
		data->philo[i].done = false;
		data->philo[i].thread_id = 0;
		i++;
	}
	return (0);
}

/// Inialisation Mutex //
int	init_mutex(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->nbr_philo);
	data->fourch = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->fourch[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->check_running, NULL);
	pthread_mutex_init(&data->writing, NULL);
	pthread_mutex_init(&data->all_miam_miam, NULL);
	return (0);
}
