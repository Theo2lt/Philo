/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_action.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 06:18:29 by tliot             #+#    #+#             */
/*   Updated: 2022/08/04 08:32:27 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_miam_miam(t_philo *philo)
{
	print_philo(philo, "is eating");
	philo->count_miam_miam++;
	pthread_mutex_lock(&philo->data->m_time_miam_miam);
	philo->last_time_miam_miam = ft_time_ms();
	pthread_mutex_unlock(&philo->data->m_time_miam_miam);
	slipe(philo->data->time_to_eat, philo);
	//usleep(1000 * philo->data->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	print_philo(philo, "is sleeping");
	slipe(philo->data->time_to_sleep, philo);
	//usleep((1000 * philo->data->time_to_sleep));
}

void	philo_think(t_philo *philo)
{
	print_philo(philo, "is thinking");
}



int	take_fourch(t_philo *philo)
{
	if(philo->data->nbr_philo == philo->id+1 && philo->data->nbr_philo != 1)
	{
		pthread_mutex_lock(&philo->data->fourch[philo->right_fourch_id]);
		print_philo(philo, "has taken a fork");
		if (philo->data->nbr_philo == 1)
		{
			pthread_mutex_unlock(&philo->data->fourch[philo->right_fourch_id]);
			return (-1);
		}
		pthread_mutex_lock(&philo->data->fourch[philo->left_fourch_id]);
		print_philo(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->fourch[philo->left_fourch_id]);
		print_philo(philo, "has taken a fork");
		if (philo->data->nbr_philo == 1)
		{
			pthread_mutex_unlock(&philo->data->fourch[philo->left_fourch_id]);
			return (-1);
		}
		pthread_mutex_lock(&philo->data->fourch[philo->right_fourch_id]);
		print_philo(philo, "has taken a fork");
	}
	return (1);
}

void	drop_fourch(t_philo *philo)
{
	pthread_mutex_unlock(&philo->data->fourch[philo->right_fourch_id]);
	pthread_mutex_unlock(&philo->data->fourch[philo->left_fourch_id]);
}

