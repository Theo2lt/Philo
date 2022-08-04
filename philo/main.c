/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:15:50 by tliot             #+#    #+#             */
/*   Updated: 2022/08/04 02:28:27 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// Thread Philo ///
void	*job(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	philo->last_time_miam_miam = ft_time_ms();
	if (philo->id % 2 == 0)
		usleep(philo->data->time_to_eat * 250);
	while (philo->data->running)
	{
		if (take_fourch(philo) == -1)
			return (NULL);
		philo_miam_miam(philo);
		drop_fourch(philo);
		if (philo->count_miam_miam == philo->data->nbr_eat)
		{
			philo->done = true;
			philo->data->count_done++;
			break ;
		}
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

/// Thread life check //
void	*check_life(void *arg)
{
	t_data	*data;
	int		i;
	int		time;

	data = (t_data *)arg;
	i = 0;
	while (42)
	{
		if (data->count_done == data->nbr_philo)
			break ;
		if (i == data->nbr_philo)
			i = 0;
		usleep(1000);
		time = ft_time_ms();
		pthread_mutex_lock(&data->all_miam_miam);
		if (!data->philo[i].done
			&& (int)(time - data->philo[i].last_time_miam_miam)
			> data->time_to_die)
		{
			pthread_mutex_lock(&data->check_running);
			print_philo(&data->philo[i], "died");
			data->running = false;
			pthread_mutex_unlock(&data->check_running);
			break ;
		}
		i++;
		pthread_mutex_lock(&data->all_miam_miam);
	}
	return (NULL);
}

/// Start Cration All Thread//
int	start_thread(t_data *data)
{
	int			i;
	pthread_t	thread_check_life;

	i = 0;
	data->time_start = ft_time_ms();
	while (i != data->nbr_philo)
	{
		if (pthread_create(&data->philo[i].thread_id,
				NULL, job, &data->philo[i]) != 0)
			return (i);
		i++;
	}
	if (pthread_create(&thread_check_life, NULL, &check_life, data) != 0)
		return (i);
	pthread_join(thread_check_life, NULL);
	i = 0;
	while (i != data->nbr_philo)
		pthread_join(data->philo[i++].thread_id, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("Error nombre Argument(s)\n");
		return (EXIT_FAILURE);
	}
	if (init_arg(&data, argv))
	{
		printf("Error valeur Argument(s)\n");
		return (EXIT_FAILURE);
	}
	if (init_mutex(&data))
	{
		printf("Error init mutex\n");
		return (EXIT_FAILURE);
	}
	init_philo(&data);
	start_thread(&data);
	fr_all(&data);
	return (EXIT_SUCCESS);
}
