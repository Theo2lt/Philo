/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 02:01:20 by tliot             #+#    #+#             */
/*   Updated: 2022/08/05 12:39:23 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_time_ms(void)
{
	struct timeval	get_time;

	gettimeofday(&get_time, NULL);
	return ((get_time.tv_sec * (uint64_t)1000) + (get_time.tv_usec / 1000));
}

void	slipe(uint64_t sleep_ms, t_philo *philo)
{
	uint64_t	wait_micro_us;
	int			i;

	wait_micro_us = sleep_ms * 1000;
	i = wait_micro_us / 50000;
	wait_micro_us = wait_micro_us % 50000;
	while (i != 0)
	{
		usleep(50000);
		if (mutex_check_running(philo) == false)
			break ;
		i--;
	}
	usleep(wait_micro_us);
}

void	print_philo(t_philo *philo, char *str)
{
	pthread_mutex_lock(&philo->data->m_running);
	if (!philo->data->running)
	{
		pthread_mutex_unlock(&philo->data->m_running);
		return ;
	}
	printf("%lu %d %s\n", ft_time_ms() - philo->data->time_start,
		philo->id, str);
	pthread_mutex_unlock(&philo->data->m_running);
}

int	ft_verif_argument(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == '+')
			i++;
		else
			return(-1);
	}
	return (ft_atoi(str));
}

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
