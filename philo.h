/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 03:53:33 by tliot             #+#    #+#             */
/*   Updated: 2022/08/02 08:46:44 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

struct s_data;

typedef struct s_philo
{
	int				id;
	pthread_t		thread_id;
	int				x_miam_miam;
	int				left_fourch_id;
	int				right_fourch_id;
	struct timeval	time_last_miam;
	struct s_data	*data;
} t_philo;

typedef struct			s_data
{
	int					nbr_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nbr_repas;
	struct timeval		first_time;
	int					isdead;
	pthread_mutex_t		miam_miam;
	pthread_mutex_t		fourch[300];
	pthread_mutex_t		writing;
	t_philo				philosophers[300];
} t_data;

#endif