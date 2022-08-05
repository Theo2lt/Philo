/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mutex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 03:53:03 by tliot             #+#    #+#             */
/*   Updated: 2022/08/05 04:54:07 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	mutex_check_running(t_philo *philo)
{
	bool	i;

	pthread_mutex_lock(&philo->data->m_running);
	if (philo->data->running)
		i = true;
	else
		i = false;
	pthread_mutex_unlock(&philo->data->m_running);
	return (i);
}

bool	mutex_change_running(t_data	*data)
{
	bool	vrf;

	vrf = true;
	pthread_mutex_lock(&data->m_done_count);
	if (data->count_done >= data->nbr_philo)
	{
		pthread_mutex_lock(&data->m_running);
		data->running = false;
		pthread_mutex_unlock(&data->m_running);
		vrf = false;
	}
	pthread_mutex_unlock(&data->m_done_count);
	return (vrf);
}

bool	mutex_check_death(t_data *data, int i)
{
	int		time;
	bool	vrf;

	time = ft_time_ms();
	vrf = true;
	pthread_mutex_lock(&data->m_time_miam_miam);
	pthread_mutex_lock(&data->m_done);
	if (!data->philo[i].done
		&& (int)(time - data->philo[i].last_time_miam_miam) > data->time_to_die)
	{
		print_philo(&data->philo[i], "died");
		pthread_mutex_lock(&data->m_running);
		data->running = false;
		pthread_mutex_unlock(&data->m_running);
		vrf = false;
	}
	pthread_mutex_unlock(&data->m_done);
	pthread_mutex_unlock(&data->m_time_miam_miam);
	return (vrf);
}

void	mutex_change_last_time_miam_miam(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->m_time_miam_miam);
	philo->last_time_miam_miam = ft_time_ms();
	pthread_mutex_unlock(&philo->data->m_time_miam_miam);
}
