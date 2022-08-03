/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:15:50 by tliot             #+#    #+#             */
/*   Updated: 2022/08/03 05:52:34 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/// INIT ARGUMENTS ///
int init_arg(t_data *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->running = true;
	if(data->nbr_philo <= 0 
		|| data->time_to_die <= 0 
		|| data->time_to_sleep <= 0
		|| data->time_to_eat <= 0)
	return (1);
	if(argv[5])
	{
		data->nbr_eat = ft_atoi(argv[5]);
		if(data->nbr_eat <= 0)
			return(1);
	}
	else
		data->nbr_eat = -1;
	return (0);
}

/// INITIALISATION DES PHILO ///
int	init_philo(t_data *data)
{
	int i;

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

/// INITIALISATON DES MUTEX //
int init_mutex(t_data *data)
{
	int	i;
	
	data->philo = malloc(sizeof(t_philo) * data->nbr_philo);
	data->fourch = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_init(&data->fourch[i],NULL);
		i++;
	}
	pthread_mutex_init(&data->writing,NULL);

	return(0);
}

void *job(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	philo->last_time_miam_miam = ft_time_ms();
	if(philo->id % 2 == 0)
	{
		philo_think(philo);
		usleep(philo->data->time_to_eat * 250);
	}
	while (philo->data->running)
	{
		if(take_fourch(philo) == -1)
			return (NULL);
		philo_miam_miam(philo);
		drop_fourch(philo);
		if(philo->count_miam_miam == philo->data->nbr_eat)
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
void *check_life(void *arg)
{
	t_data *data;
	int i;
	int time;

	data = (t_data *)arg;
	i = 0;
	while (42)
	{
		if(data->count_done == data->nbr_philo)
			break;
		if(i == data->nbr_philo)
			i = 0;
		usleep(1000);
		time = ft_time_ms();
		if(!data->philo[i].done && (int)(time - data->philo[i].last_time_miam_miam) > data->time_to_die)
		{
			print_philo(&data->philo[i],"died");
			data->running = false;
			break ;
		}
		i++;
	}
	return (NULL);
}
int start_thread(t_data *data)
{
	int i;
	pthread_t thread_check_life;
	
	i = 0;
	while (i != data->nbr_philo)
	{
		if(pthread_create(&data->philo[i].thread_id,NULL,job,&data->philo[i]) != 0)
			return(i);
		i++;
	}
	if(pthread_create(&thread_check_life, NULL, &check_life,data) != 0)
		return(i);
	pthread_join(thread_check_life,NULL);
	
	i = 0;
	while (i != data->nbr_philo)
	{
		pthread_join(data->philo[i].thread_id,NULL);
		i++;
	}
	return(0);
}



void fr_all(t_data *data)
{
	int i;

	i = 0;
	while (i < data->nbr_philo)
		pthread_mutex_destroy(&data->fourch[i++]);
	free(data->fourch);
	pthread_mutex_destroy(&data->writing);
	free(data->philo);

}


int main(int argc, char **argv)
{
	t_data data;
	
	if(argc != 5 && argc != 6)
	{
		printf("Error nombre Argument(s)\n");
		return (EXIT_FAILURE);
	}
	if(init_arg(&data, argv))
	{
		printf("Error valeur Argument(s)\n");
		return (EXIT_FAILURE);
	}
	if(init_mutex(&data))
	{
		printf("Error init mutex\n");
		return (EXIT_FAILURE);
	}
	init_philo(&data);
	start_thread(&data);
	fr_all(&data);
	return (EXIT_SUCCESS);
}