/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tliot <tliot@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 02:01:20 by tliot             #+#    #+#             */
/*   Updated: 2022/08/03 05:41:47 by tliot            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t ft_time_ms(void)
{
    struct timeval get_time;
    
    gettimeofday(&get_time, NULL);
    return ((get_time.tv_sec * (uint64_t)1000) + (get_time.tv_usec / 1000));
}

void	slipe(uint64_t sleep_ms, t_philo *philo)
{
	uint64_t	time;

	time = ft_time_ms() + sleep_ms;
	while (ft_time_ms() < time && philo->data->running > 0)
		usleep(50);
}


void	print_philo(t_philo *philo, char *str)
{
	if (!philo->data->running)
		return ;
	pthread_mutex_lock(&philo->data->writing);
	printf("%lu %d %s\n", ft_time_ms(), philo->id, str);
	pthread_mutex_unlock(&philo->data->writing);
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