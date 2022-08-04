/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 06:29:03 by tliot             #+#    #+#             */
/*   Updated: 2022/08/04 06:04:34 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	fr_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
		pthread_mutex_destroy(&data->fourch[i++]);
	free(data->fourch);
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->m_time_miam_miam);
	pthread_mutex_destroy(&data->m_done);
	pthread_mutex_destroy(&data->m_done_count);
	pthread_mutex_destroy(&data->m_running);
	free(data->philo);
}
