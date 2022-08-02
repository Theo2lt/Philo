/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 04:15:50 by tliot             #+#    #+#             */
/*   Updated: 2022/08/02 09:04:03 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	unsigned int	i;
	int				signe;
	int				result;

	signe = 1;
	i = 0;
	result = 0;
	while (str[i] == 9 || (str[i] >= 10 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe *= -1;
		i++;
	}
	i--;
	while (str[++i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - 48);
		if (signe > 0 && i >= 25)
			return (-1);
		else if (signe < 0 && i >= 26)
			return (0);
	}
	return (result * signe);
}

int init_arg(t_data *data, char **argv)
{
	data->nbr_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	data->isdead = 0;
	if((data->nbr_philo < 0 && data->nbr_philo > 300)
		|| data->time_to_die <= 0 
		|| data->time_to_sleep <= 0
		|| data->time_to_eat <= 0)
	return (1);
	if(argv[5])
	{
		data->nbr_repas = ft_atoi(argv[5]);
		if(data->nbr_repas <= 0)
			return(1);
	}
	else
		data->nbr_repas = -1;
	return (0);
}

int	init_philo(t_data *data)
{
	int i;

	i = 0;
	while (i != data->nbr_philo)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].x_miam_miam = 0;
		data->philosophers[i].left_fourch_id = i;
		data->philosophers[i].right_fourch_id = (i + 1) % data->nbr_philo;
		//data->philosophers[i].time_last_miam = 0;
		data->philosophers[i].data = data;
		i++;
	}
	return (0);
}

int init_mutex(t_data *data)
{
	int	i;
	
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->miam_miam), NULL))
		return (1);
	return (0);
	i = 0;
	while (i != data->nbr_philo)
	{
		pthread_mutex_init(&(data->fourch[i++]),NULL);
	}

	return(0);
}

void *jobs(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->writing);
	gettimeofday(&philo->time_last_miam, NULL);
	printf("-------------------------------------------\n");
	printf("             id : [%d]\n",philo->id);
	printf("      thread_id : [%ld]\n",philo->thread_id);
	printf(" left_fourch_id : [%d]\n",philo->left_fourch_id);
	printf("right_fourch_id : [%d]\n",philo->right_fourch_id);
	printf(" time_last_miam : [%ld]\n", philo->time_last_miam.tv_usec - philo->data->first_time.tv_usec);
	printf("-------------------------------------------\n");
	pthread_mutex_unlock(&philo->data->writing);
	return ((void *)1 );
}

int start_launcher(t_data *data)
{
	int i;
	t_philo *philo;

	philo = data->philosophers;
	gettimeofday(&data->first_time, NULL);
	i = 0;
	while (i != data->nbr_philo)
	{
		
		if(pthread_create(&(philo[i]).thread_id,NULL,jobs,&philo[i]))
			return(1);
		
		
		i++;
	}
	i = 0;
	while (i != data->nbr_philo)
	{
		pthread_join(philo[i].thread_id,NULL);
		i++;
	}
	
	return (0);
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
	start_launcher(&data);
	return (EXIT_SUCCESS);
}